This system features an MFRC522 RFID reader, 4x3 keypad , an OLED and a HC-05 bluetooth
module integrated with an STM32 microcontroller. Each product is uniquely
identified by a RFID UID(Unique Identity Number) of the corresponding tag
attached to each product.As customers scan products to the RFID module its
product id and price is displayed on an OLED screen. The data will also be sent to
the customer's cell phone through a Bluetooth application by an HC05 bluetooth
module.An open source app “Bluetooth Terminal”is used to enhance user interface.
The total cost updates in real-time as more items are added or removed,
allowing customers to make informed decisions and easily track their spending.If a
customer changes their mind about a product, they can remove it by scanning the
same product again, and the system will automatically deduct the corresponding
amount from the total.The user inputs are taken from the keypad, where for certain
button press, specific content is displayed on the OLED and on the app to the user
for a more user friendly experience during shopping.
