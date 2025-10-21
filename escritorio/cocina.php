<?php
header('Content-Type: application/json; charset=utf-8');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');

// Configuración de la base de datos
$host = 'localhost';
$dbname = 'buengusto';
$username = 'root';
$password = '';

try {
    $pdo = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8mb4", $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
    // Manejar peticiones POST (confirmar pedido)
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $input = json_decode(file_get_contents('php://input'), true);
        
        // Acción: Confirmar pedido
        if (isset($input['accion']) && $input['accion'] === 'confirmar') {
            $id_pedido = isset($input['id_pedido']) ? (int)$input['id_pedido'] : 0;
            
            if ($id_pedido <= 0) {
                echo json_encode([
                    'success' => false,
                    'message' => 'ID de pedido inválido'
                ], JSON_UNESCAPED_UNICODE);
                exit;
            }
            
            // Verificar que el pedido existe y está en estado pendiente
            $sql_check = "SELECT id, estado, numero_pedido FROM pedidos WHERE id = :id_pedido AND activo = 1";
            $stmt_check = $pdo->prepare($sql_check);
            $stmt_check->execute(['id_pedido' => $id_pedido]);
            $pedido = $stmt_check->fetch(PDO::FETCH_ASSOC);
            
            if (!$pedido) {
                echo json_encode([
                    'success' => false,
                    'message' => 'Pedido no encontrado'
                ], JSON_UNESCAPED_UNICODE);
                exit;
            }
            
            if ($pedido['estado'] !== 'pendiente') {
                echo json_encode([
                    'success' => false,
                    'message' => 'El pedido ya fue confirmado anteriormente'
                ], JSON_UNESCAPED_UNICODE);
                exit;
            }
            
            // Actualizar el estado del pedido a 'confirmado'
            $sql_update = "UPDATE pedidos SET estado = 'confirmado' WHERE id = :id_pedido";
            $stmt_update = $pdo->prepare($sql_update);
            
            if ($stmt_update->execute(['id_pedido' => $id_pedido])) {
                echo json_encode([
                    'success' => true,
                    'message' => 'Pedido #' . $pedido['numero_pedido'] . ' confirmado exitosamente',
                    'pedido_id' => $id_pedido,
                    'numero_pedido' => $pedido['numero_pedido']
                ], JSON_UNESCAPED_UNICODE);
            } else {
                echo json_encode([
                    'success' => false,
                    'message' => 'Error al actualizar el estado del pedido'
                ], JSON_UNESCAPED_UNICODE);
            }
            exit;
        }
        
        // Acción: Asignar repartidor
        if (isset($input['accion']) && $input['accion'] === 'asignar_repartidor') {
            $id_pedido = isset($input['id_pedido']) ? (int)$input['id_pedido'] : 0;
            $repartidor_id = isset($input['repartidor_id']) ? (int)$input['repartidor_id'] : 0;
            
            if ($id_pedido <= 0 || $repartidor_id <= 0) {
                echo json_encode([
                    'success' => false,
                    'message' => 'Datos inválidos'
                ], JSON_UNESCAPED_UNICODE);
                exit;
            }
            
            // Verificar que el pedido existe
            $sql_check = "SELECT id, numero_pedido FROM pedidos WHERE id = :id_pedido AND activo = 1";
            $stmt_check = $pdo->prepare($sql_check);
            $stmt_check->execute(['id_pedido' => $id_pedido]);
            $pedido = $stmt_check->fetch(PDO::FETCH_ASSOC);
            
            if (!$pedido) {
                echo json_encode([
                    'success' => false,
                    'message' => 'Pedido no encontrado'
                ], JSON_UNESCAPED_UNICODE);
                exit;
            }
            
            // Verificar que el repartidor existe y está activo
            $sql_check_rep = "SELECT id, nombre, apellido FROM usuarios WHERE id = :repartidor_id AND rol = 'repartidor' AND activo = 1";
            $stmt_check_rep = $pdo->prepare($sql_check_rep);
            $stmt_check_rep->execute(['repartidor_id' => $repartidor_id]);
            $repartidor = $stmt_check_rep->fetch(PDO::FETCH_ASSOC);
            
            if (!$repartidor) {
                echo json_encode([
                    'success' => false,
                    'message' => 'Repartidor no encontrado o no disponible'
                ], JSON_UNESCAPED_UNICODE);
                exit;
            }
            
            // Asignar repartidor al pedido
            $sql_update = "UPDATE pedidos SET repartidor_id = :repartidor_id WHERE id = :id_pedido";
            $stmt_update = $pdo->prepare($sql_update);
            
            if ($stmt_update->execute(['repartidor_id' => $repartidor_id, 'id_pedido' => $id_pedido])) {
                echo json_encode([
                    'success' => true,
                    'message' => 'Repartidor asignado exitosamente al pedido #' . $pedido['numero_pedido'],
                    'pedido_id' => $id_pedido,
                    'repartidor_id' => $repartidor_id,
                    'repartidor_nombre' => $repartidor['nombre'] . ' ' . $repartidor['apellido']
                ], JSON_UNESCAPED_UNICODE);
            } else {
                echo json_encode([
                    'success' => false,
                    'message' => 'Error al asignar el repartidor'
                ], JSON_UNESCAPED_UNICODE);
            }
            exit;
        }
        
        // Si la acción no es reconocida
        echo json_encode([
            'success' => false,
            'message' => 'Acción no reconocida'
        ], JSON_UNESCAPED_UNICODE);
        exit;
    }
    
    // Manejar peticiones GET (obtener pedidos)
    if ($_SERVER['REQUEST_METHOD'] === 'GET' || $_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
        // Consulta principal para obtener pedidos activos
        $sql_pedidos = "
            SELECT 
                p.id,
                p.numero_pedido,
                p.tipo_pedido,
                p.fecha_pedido,
                p.fecha_entrega_programada,
                p.direccion_entrega,
                p.telefono_contacto,
                p.metodo_pago,
                p.estado,
                p.subtotal,
                p.precio_delivery,
                p.total,
                p.comentarios_cliente,
                u.nombre AS cliente_nombre,
                u.apellido AS cliente_apellido,
                u.telefono AS cliente_telefono,
                r.nombre AS repartidor_nombre,
                r.apellido AS repartidor_apellido,
                r.id AS repartidor_id,
                z.nombre AS zona_nombre,
                z.precio_delivery AS zona_precio,
                z.tiempo_estimado AS zona_tiempo_estimado
            FROM pedidos p
            INNER JOIN usuarios u ON p.usuario_id = u.id
            LEFT JOIN usuarios r ON p.repartidor_id = r.id AND r.rol = 'repartidor'
            LEFT JOIN zonas_delivery z ON p.zona_delivery_id = z.id
            WHERE p.activo = 1 
            AND p.estado IN ('pendiente', 'confirmado', 'en_preparacion')
            ORDER BY 
                CASE 
                    WHEN p.estado = 'pendiente' THEN 1
                    WHEN p.estado = 'confirmado' THEN 2
                    WHEN p.estado = 'en_preparacion' THEN 3
                END,
                p.fecha_pedido ASC
        ";
        
        $stmt_pedidos = $pdo->prepare($sql_pedidos);
        $stmt_pedidos->execute();
        $pedidos = $stmt_pedidos->fetchAll(PDO::FETCH_ASSOC);
        
        // Para cada pedido, obtener sus items con productos y condimentos
        foreach ($pedidos as &$pedido) {
            // Obtener items del pedido
            $sql_items = "
                SELECT 
                    pi.id,
                    pi.cantidad,
                    pi.precio_unitario,
                    pi.precio_total,
                    pr.nombre AS producto_nombre,
                    pr.descripcion AS producto_descripcion,
                    pr.imagen AS producto_imagen,
                    pr.tiempo_preparacion,
                    c.nombre AS categoria_nombre
                FROM pedido_items pi
                INNER JOIN productos pr ON pi.producto_id = pr.id
                INNER JOIN categorias c ON pr.categoria_id = c.id
                WHERE pi.pedido_id = :pedido_id
            ";
            
            $stmt_items = $pdo->prepare($sql_items);
            $stmt_items->execute(['pedido_id' => $pedido['id']]);
            $items = $stmt_items->fetchAll(PDO::FETCH_ASSOC);
            
            // Para cada item, obtener sus condimentos
            foreach ($items as &$item) {
                $sql_condimentos = "
                    SELECT 
                        co.id,
                        co.nombre,
                        co.tipo
                    FROM item_condimentos ic
                    INNER JOIN condimentos co ON ic.condimento_id = co.id
                    WHERE ic.pedido_item_id = :item_id
                    AND co.activo = 1
                ";
                
                $stmt_condimentos = $pdo->prepare($sql_condimentos);
                $stmt_condimentos->execute(['item_id' => $item['id']]);
                $condimentos = $stmt_condimentos->fetchAll(PDO::FETCH_ASSOC);
                
                $item['condimentos'] = $condimentos;
            }
            
            $pedido['items'] = $items;
            
            // Calcular total de unidades
            $total_unidades = 0;
            foreach ($items as $item) {
                $total_unidades += $item['cantidad'];
            }
            $pedido['total_unidades'] = $total_unidades;
        }
        
        // Separar pedidos por estado
        $pedidos_pendientes = array_filter($pedidos, function($p) {
            return $p['estado'] === 'pendiente';
        });
        
        $pedidos_confirmados = array_filter($pedidos, function($p) {
            return $p['estado'] === 'confirmado' || $p['estado'] === 'en_preparacion';
        });
        
        // Obtener repartidores disponibles
        $sql_repartidores = "
            SELECT 
                id,
                nombre,
                apellido,
                telefono,
                estado_disponibilidad
            FROM usuarios
            WHERE rol = 'repartidor' 
            AND activo = 1
            AND estado_disponibilidad = 1
            ORDER BY nombre ASC
        ";
        
        $stmt_repartidores = $pdo->prepare($sql_repartidores);
        $stmt_repartidores->execute();
        $repartidores = $stmt_repartidores->fetchAll(PDO::FETCH_ASSOC);
        
        // Respuesta JSON
        $response = [
            'success' => true,
            'pedidos_pendientes' => array_values($pedidos_pendientes),
            'pedidos_confirmados' => array_values($pedidos_confirmados),
            'repartidores_disponibles' => $repartidores,
            'total_pedidos' => count($pedidos),
            'timestamp' => date('Y-m-d H:i:s')
        ];
        
        echo json_encode($response, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT);
    }
    
} catch (PDOException $e) {
    $response = [
        'success' => false,
        'error' => 'Error de base de datos',
        'message' => $e->getMessage()
    ];
    
    echo json_encode($response, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT);
}
?>