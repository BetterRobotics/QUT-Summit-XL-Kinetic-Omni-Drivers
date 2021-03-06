QUT Summit XL
=============
<b># NOTE:</b> This workspace is designed for an Summit XL OMNI-drive platform using the Mecanum wheels, it's running the latest drivers for the Motor Controllers, Summit XL platform and ROS kinetic.

This work was part of a larger project at QUT with contributions from Dimity Miller, Serena Mou and myself Ben Fogarty!

  Install the peak system CANBUS driver module using the following commands:
  --------------------------------------------------------------------------
  
  Setup "libpopt.dev" dependency by install libpopt-dev library into the system:
  ```bash
  sudo apt-get install libpopt-dev
  ```
  Untar the file:
  ```bash
  tar -xzf <path to driver> && cd peak-linux-driver-7.15.2
  ```
  Make Install:
  ```bash
  make clean && make NET=NO_NETDEV_SUPPORT && sudo make install
  ```
  Connect Peak USB-CAN converter and check that the OS loads the module:
  ```bash
  lsmod | grep pcan
  ls /dev/pcanusb0
  ```
  Check that the peakcan module is compiled to be used with NO NETDEV SUPPORT:
  ```bash
  cat /proc/pcan
  ```
  
  You should see:  -NA- under ndev
  ```bash
  *------------- PEAK-System CAN interfaces (www.peak-system.com) -------------
  *-------------------------- Release_20120319_n (7.5.0) ----------------------
  *---------------- [mod] [isa] [pci] [dng] [par] [usb] [pcc] -----------------
  *--------------------- 1 interfaces @ major 250 found -----------------------
  *n -type- ndev --base-- irq --btr- --read-- --write- --irqs-- -errors- status
  32    usb -NA- ffffffff 255 0x0014 00000005 00000034 00000168 00000075 0x000cCop 
  ```

  Install ROS catkin workspace:
  -----------------------------
  
  Copy caktin_ws_kinetic to desired location and make workspace as per ROS instructions here:  http://wiki.ros.org/catkin/Tutorials/create_a_workspace.
  
