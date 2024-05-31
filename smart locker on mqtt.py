import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import paho.mqtt.client as mqtt

class MQTTBridge(Node):

    def __init__(self):
        super().__init__('mqtt_bridge')
        self.publisher_ = self.create_publisher(String, 'lock_status', 10)
        self.subscription = self.create_subscription(
            String,
            'lock_command',
            self.command_callback,
            10)
        self.subscription  # prevent unused variable warning

        self.mqtt_client = mqtt.Client()
        self.mqtt_client.on_connect = self.on_connect
        self.mqtt_client.on_message = self.on_message
        self.mqtt_client.connect('your_MQTT_BROKER_ADDRESS', 1883, 60)
        self.mqtt_client.loop_start()

    def command_callback(self, msg):
        command = msg.data
        self.mqtt_client.publish('lock_command', command)
        self.get_logger().info(f'Sent command: {command}')

    def on_connect(self, client, userdata, flags, rc):
        self.get_logger().info(f'Connected to MQTT broker with result code {rc}')
        client.subscribe('lock_status')

    def on_message(self, client, userdata, msg):
        status = msg.payload.decode()
        self.get_logger().info(f'Received status: {status}')
        ros_msg = String()
        ros_msg.data = status
        self.publisher_.publish(ros_msg)

def main(args=None):
    rclpy.init(args=args)
    mqtt_bridge = MQTTBridge()
    rclpy.spin(mqtt_bridge)
    mqtt_bridge.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
