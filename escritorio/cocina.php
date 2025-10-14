<?php
// Conexión a la base de datos
$host = 'localhost';
$dbname = 'tu_base_datos';
$username = 'tu_usuario';
$password = 'tu_contraseña';

try {
    $pdo = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8mb4", $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
    // Consulta SQL para obtener todos los datos de pedidos
    $sql = "SELECT 
                id,
                numero_pedido,
                usuario_id,
                tipo_pedido,
                fecha_pedido,
                fecha_entrega_programada,
                direccion_entrega,
                telefono_contacto,
                metodo_pago,
                estado,
                subtotal,
                precio_delivery,
                total,
                zona_delivery_id,
                repartidor_id,
                cajero_id,
                comentarios_cliente,
                activo
            FROM pedidos
            WHERE activo = 1
            ORDER BY fecha_pedido DESC";
    
    $stmt = $pdo->prepare($sql);
    $stmt->execute();
    
    // Obtener todos los resultados
    $pedidos = $stmt->fetchAll(PDO::FETCH_ASSOC);
    
    // Codificar a JSON
    $json_pedidos = json_encode($pedidos, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT);
    
    // Mostrar el JSON
    header('Content-Type: application/json; charset=utf-8');
    echo $json_pedidos;
    
    // O si necesitas almacenarlo en una variable para procesarlo
    // $data = json_decode($json_pedidos, true);
    
} catch(PDOException $e) {
    echo json_encode([
        'error' => true,
        'mensaje' => 'Error en la conexión: ' . $e->getMessage()
    ]);
}

// Ejemplo alternativo: Consulta con filtros específicos
/*
$sql = "SELECT * FROM pedidos 
        WHERE estado = :estado 
        AND activo = 1 
        ORDER BY fecha_pedido DESC 
        LIMIT 50";

$stmt = $pdo->prepare($sql);
$stmt->execute(['estado' => 'pendiente']);
$pedidos = $stmt->fetchAll(PDO::FETCH_ASSOC);
$json_pedidos = json_encode($pedidos, JSON_UNESCAPED_UNICODE);
*/

// Ejemplo: Consulta con JOIN para obtener información relacionada
/*
$sql = "SELECT 
            p.*,
            u.nombre as nombre_usuario,
            r.nombre as nombre_repartidor,
            z.nombre as nombre_zona
        FROM pedidos p
        LEFT JOIN usuarios u ON p.usuario_id = u.id
        LEFT JOIN repartidores r ON p.repartidor_id = r.id
        LEFT JOIN zonas_delivery z ON p.zona_delivery_id = z.id
        WHERE p.activo = 1
        ORDER BY p.fecha_pedido DESC";
*/
?>