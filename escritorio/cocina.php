<?php
header('Content-Type: application/json; charset=utf-8');
header('Access-Control-Allow-Origin: *');

// Configuración de la base de datos
$host = 'localhost';
$dbname = 'buengusto';
$username = 'root';
$password = '';

try {
    $pdo = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8mb4", $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
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
    
} catch (PDOException $e) {
    $response = [
        'success' => false,
        'error' => 'Error de base de datos',
        'message' => $e->getMessage()
    ];
    
    echo json_encode($response, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT);
}
?>