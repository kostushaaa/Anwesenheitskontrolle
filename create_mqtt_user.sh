#!/bin/sh

# Checking the arguments
if [ -z "$1" ] || [ -z "$2" ]; then
  echo "Usage: $0 <username> <password>"
  exit 1
fi

USERNAME=$1
PASSWORD=$2
CONTAINER_NAME="mqtt5_broker" # name of container Mosquitto
PWFILE="/mosquitto/config/pwfile"

# In the container terminal
docker exec "$CONTAINER_NAME" sh -c "
  if [ ! -f $PWFILE ]; then
    mosquitto_passwd -c -b $PWFILE $USERNAME $PASSWORD
  else
    mosquitto_passwd -b $PWFILE $USERNAME $PASSWORD
  fi &&
  chown root:root $PWFILE &&
  chmod 0700 $PWFILE
"

echo "User $USERNAME added/updated successfully in $CONTAINER_NAME."
