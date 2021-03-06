#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include <ensenso/HeadPose.h> //local msg communicator of 5-d pose
#include <geometry_msgs/Twist.h>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include <Eigen/Core>
/*@brief sends the pose info on the LAN/WAN to 
* every listener on the network that subscribes to the pose of the head
*
*/
namespace udp
{
	class sender
	{
	public:
		sender(boost::asio::io_service& io_service,
		        const boost::asio::ip::address& multicast_address, 
		        const ensenso::HeadPose& pose_info);
		sender(boost::asio::io_service& io_service,
		        const boost::asio::ip::address& multicast_address, 
		        const geometry_msgs::Twist& u_valves);
		//constructor control law + ref + headpose
		sender(boost::asio::io_service& io_service,
		        const boost::asio::ip::address& multicast_address, 
		        const geometry_msgs::Twist& u_valves, 
		        const Eigen::Vector3d& ref, 
		        const ensenso::HeadPose& pose_info);

		void handle_send_to(const boost::system::error_code& error);
		void handle_timeout(const boost::system::error_code& error);
	private:
	  boost::asio::ip::udp::endpoint endpoint_;
	  boost::asio::ip::udp::socket socket_;
	  boost::asio::deadline_timer timer_;
	  std::ostringstream os, osc, osall;
	  ensenso::HeadPose pose;
	  geometry_msgs::Twist u_valves_;
	  Eigen::Vector3d ref_;
	  std::string message_;
	};
}