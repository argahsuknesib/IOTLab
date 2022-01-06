import binascii
import struct
import time
from digi import ble


def get_characteristics_from_uuids(connection, service_uuid, characteristic_uuid):
    services = list(connection.gattc_services(service_uuid))
    print("services: \n")
    print(services)
    if len(services):
        # Assume that there is only one service per UUID, take the first one
        my_service = services[0]

        characteristics = list(connection.gattc_characteristics(my_service, characteristic_uuid))
        return characteristics
    # Couldn't find specified characteristic, return an empy list
    return []


# Change these two variables to your device's address and address type.
# This sample expects a Thunderboard React to be used.
# The address and address type can be discovered using ble.gap_scan().
THUNDERBOARD_ADDRESS = "FC:F5:C4:0A:0D:FA"
address_type = ble.ADDR_TYPE_PUBLIC

# Put address into bytes object (without colons)
address = binascii.unhexlify(THUNDERBOARD_ADDRESS.replace(':', ''))

# The service and characteristic UUIDs
io_service_uuid = 0x1815
io_characteristic_uuid = 0x1801



ble.active(True)
print("Attempting connection to: {}".format(THUNDERBOARD_ADDRESS))
with ble.gap_connect(address_type, address) as conn:
    print("connected")

    # There is only one temperature service and characteristic, so use the first and only one in the list
    # There are a couple of IO characteristics, we are looking for the one we can write to
    io_characteristics = get_characteristics_from_uuids(conn, io_service_uuid, io_characteristic_uuid)

    print(io_characteristics)
    led_characteristic = None
    for charact in io_characteristics:
        # Find the characteristics that is writable by looking at the properties of the characteristics
        properties = charact[2]
        if properties & ble.PROP_WRITE:
            led_characteristic = charact
            print("Using LED char {}".format(led_characteristic))

    if led_characteristic is None:
        print("Did not find the LED characteristic")
    else:
        # Blink the LED and read the temperature
        while True:

            # Turn on the LED
            conn.gattc_write_characteristic(led_characteristic, b'\x01')
