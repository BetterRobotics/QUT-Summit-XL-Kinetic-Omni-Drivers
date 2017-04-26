// Generated by gencpp from file summit_xl_web/RecordVideoRequest.msg
// DO NOT EDIT!


#ifndef SUMMIT_XL_WEB_MESSAGE_RECORDVIDEOREQUEST_H
#define SUMMIT_XL_WEB_MESSAGE_RECORDVIDEOREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace summit_xl_web
{
template <class ContainerAllocator>
struct RecordVideoRequest_
{
  typedef RecordVideoRequest_<ContainerAllocator> Type;

  RecordVideoRequest_()
    : startRecording(0)  {
    }
  RecordVideoRequest_(const ContainerAllocator& _alloc)
    : startRecording(0)  {
  (void)_alloc;
    }



   typedef int16_t _startRecording_type;
  _startRecording_type startRecording;




  typedef boost::shared_ptr< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> const> ConstPtr;

}; // struct RecordVideoRequest_

typedef ::summit_xl_web::RecordVideoRequest_<std::allocator<void> > RecordVideoRequest;

typedef boost::shared_ptr< ::summit_xl_web::RecordVideoRequest > RecordVideoRequestPtr;
typedef boost::shared_ptr< ::summit_xl_web::RecordVideoRequest const> RecordVideoRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace summit_xl_web

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8ea5cfe0d00a46593d72b2f1e782e82f";
  }

  static const char* value(const ::summit_xl_web::RecordVideoRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8ea5cfe0d00a4659ULL;
  static const uint64_t static_value2 = 0x3d72b2f1e782e82fULL;
};

template<class ContainerAllocator>
struct DataType< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "summit_xl_web/RecordVideoRequest";
  }

  static const char* value(const ::summit_xl_web::RecordVideoRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int16 startRecording\n\
";
  }

  static const char* value(const ::summit_xl_web::RecordVideoRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.startRecording);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct RecordVideoRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::summit_xl_web::RecordVideoRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::summit_xl_web::RecordVideoRequest_<ContainerAllocator>& v)
  {
    s << indent << "startRecording: ";
    Printer<int16_t>::stream(s, indent + "  ", v.startRecording);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SUMMIT_XL_WEB_MESSAGE_RECORDVIDEOREQUEST_H