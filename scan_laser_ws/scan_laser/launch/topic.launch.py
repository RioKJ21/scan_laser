from launch import LaunchDescription
import launch_ros.actions
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument

def generate_launch_description():
	scantopic = LaunchConfiguration('scantopic', default = "/scan")
	queue_size = LaunchConfiguration('queue_size', default = 10.0)
	return LaunchDescription ([
		DeclareLaunchArgument('scantopic', default_value = scantopic,),
		DeclareLaunchArgument('queue_size', default_value = queue_size,),
		launch_ros.actions.Node(
			package = 'scan_laser',
			executable = 'laser_rio',
			parameters = [{
				'scantopic' : scantopic,
				'queue_size' : queue_size,
				}],
				output = 'screen', 
				respawn = True,
				respawn_delay = 1,),
				])
