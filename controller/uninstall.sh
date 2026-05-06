#!/bin/bash

echo "=========================="
echo "Removing App controller"


LIBPANDA_USER=$(cat /etc/libpanda.d/libpanda_usr)

# Disable the installed services:
echo " - Disabling startup scripts..."
systemctl disable controller


# Here is where we remove scripts, services, etc.
echo " - Removing scripts..."
cd
if [ "x"`systemctl list-units | grep -c controller.service` = "x1" ]; then
    echo "Uninstalling controller.service"

    source /home/$LIBPANDA_USER/catkin_ws/devel/setup.bash
    rosrun robot_upstart uninstall controller
fi

systemctl daemon-reload # if needed
