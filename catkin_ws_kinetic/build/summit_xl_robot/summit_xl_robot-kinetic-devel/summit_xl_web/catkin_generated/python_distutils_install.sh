#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web"

# snsure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/summit/catkin_ws_kinetic/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/summit/catkin_ws_kinetic/install/lib/python2.7/dist-packages:/home/summit/catkin_ws_kinetic/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/summit/catkin_ws_kinetic/build" \
    "/usr/bin/python" \
    "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/setup.py" \
    build --build-base "/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/summit/catkin_ws_kinetic/install" --install-scripts="/home/summit/catkin_ws_kinetic/install/bin"
