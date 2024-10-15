/*cart.c
 *This file contains the functions performing the operations related to the cart
 * AUTHOR -Aysvarya Gopinath
 * 20,April 2024
 */
#include "cart.h"


//structure for each tag/ product correspondingly
typedef struct products {
	uint8_t count; // total number of times each tag is scanned
	uint8_t amt; // price of product corresponding to each tag
	char tag_id[20]; // tag id
} product_t;

product_t pid[5];  // array to hold tags

char tag_id_1[20] = "e39a9fb";     //product id 1
char tag_id_2[20] = "f3079afb";     //product id 2
char tag_id_3[20] = "933298fb";   //product id 3
char tag_id_4[20] = "13039dfb";   //product id 4

char bill[10] = "9"; // bill summary
char num[5] = "0"; // number of products
char sum[5] = "8"; // total amount

char received_string[5]; // to store user input
uint8_t rfid_id[10] = { 0 };  // read unique identity of each rfid  tag
char sNum[5]; // temporary  buffer
int added_count = 0;      // keeps count of products added to cart
int removed_count = 0;    // keeps count of products removed from cart
int tot_sum = 0; // total sum of items
int tot_num = 0; // total number of items

void tags_init(void) {
	// initial count of tags
	pid[0].count = 0; // id 1
	pid[1].count = 0; // id 2
	pid[2].count = 0;   // id 3
	pid[3].count = 0; // id 4

	//defining the price of each product corresponding to each tag
	pid[0].amt = 50; // id 1
	pid[1].amt = 70; // id 2
	pid[2].amt = 80;   // id 3
	pid[3].amt = 100; // id 4

	strcpy(pid[0].tag_id, tag_id_1); // product id 1
	strcpy(pid[1].tag_id, tag_id_2); // product id 2
	strcpy(pid[2].tag_id, tag_id_3); // product id 3
	strcpy(pid[3].tag_id, tag_id_4); // product id 4
}

void add_item(void) {
	//read the card id
	if (rc522_check_card(rfid_id)) {
		sprintf(sNum, "%x%x%x%x", rfid_id[0], rfid_id[1], rfid_id[2],
				rfid_id[3]); // store the id as a string

		if (strcmp(sNum, pid[0].tag_id) == 0) // if product id 1
				{
			if ((pid[0].count == 0) || (pid[0].count % 2 == 0)) // count is even
					{
				pid[0].count++; // number of times id 1 is scanned
				tot_num++; //then add product count  to cart
				tot_sum = tot_sum + pid[0].amt;  // adds the amount of id 1 to total
				added[added_count++] = 1; // add id to keep track of added items
				oled_gotoXY(0, 0); // display related content on the screen
				oled_puts(" Product ID 1", &Font_7x10, 1);
				oled_gotoXY(0, 10);
				oled_puts(" ADDED", &Font_7x10, 1);
				oled_gotoXY(0, 20);
				oled_puts(" + 50$", &Font_7x10, 1);
				oled_update_screen(); //display
			}
			else if (pid[0].count % 2 != 0) // count is odd
					{ // when the same card is tapped again ,
				pid[0].count--; //then then remove item from cart
				tot_num--; // decrement the total number of items in cart
				tot_sum = tot_sum - pid[0].amt;  // remove the amount from total sum
				removed[removed_count++] = 1; // add the id to the removed array
				oled_gotoXY(0, 0); // display related content on  screen
				oled_puts(" Product ID 1", &Font_7x10, 1);
				oled_gotoXY(0, 10);
				oled_puts(" REMOVED", &Font_7x10, 1);
				oled_gotoXY(0, 20);
				oled_puts(" - 50$", &Font_7x10, 1);
				oled_update_screen(); //display

			}

		} else if (strcmp(sNum, pid[1].tag_id) == 0) {    // product id 2
			if ((pid[1].count == 0) || (pid[1].count % 2 == 0)) // count is even
					{
				pid[1].count++; // number of times id 2 is scanned
				tot_num++;  //then add product count to cart
				tot_sum = tot_sum + pid[1].amt;// adds the amount of id 2 to total
				added[added_count++] = 2; // add id to keep track of added items
				oled_gotoXY(0, 0);// display related content on  screen
				oled_puts(" Product ID 2", &Font_7x10, 1);
				oled_gotoXY(0, 10);
				oled_puts(" ADDED", &Font_7x10, 1);
				oled_gotoXY(0, 20);
				oled_puts(" + 70$", &Font_7x10, 1);
				oled_update_screen(); //display
			} else if (pid[1].count % 2 != 0) // count is odd
					{ // when the same card is tapped again ,
				pid[1].count--; //then then remove item from cart
				tot_num--;// decrement the total number of items in cart
				tot_sum = tot_sum - pid[1].amt;// remove the amount from total sum
				removed[removed_count++] = 2; // add the id to the removed array
				oled_gotoXY(0, 0);// display related content on  screen
				oled_puts(" Product ID 2", &Font_7x10, 1);
				oled_gotoXY(0, 10);
				oled_puts(" REMOVED", &Font_7x10, 1);
				oled_gotoXY(0, 20);
				oled_puts(" - 70$", &Font_7x10, 1);
				oled_update_screen(); //display

			}
		} else if (strcmp(sNum, pid[2].tag_id) == 0) {     // product id 3
			if ((pid[2].count == 0) || (pid[2].count % 2 == 0)) // count is even
					{
				pid[2].count++; // number of times id 3 is scanned
				tot_num++;  //then add product count to cart
				tot_sum = tot_sum + pid[2].amt;// adds the amount of id 3 to total
				added[added_count++] = 3; // add id to keep track of added items
				oled_gotoXY(0, 0);// display related content on  screen
				oled_puts(" Product ID 3 ", &Font_7x10, 1);
				oled_gotoXY(0, 10);
				oled_puts(" ADDED", &Font_7x10, 1);
				oled_gotoXY(0, 20);
				oled_puts(" + 80$", &Font_7x10, 1);
				oled_update_screen(); //display
			} else if (pid[2].count % 2 != 0) // count is odd
					{ // when the same card is tapped again ,
				pid[2].count--; //then then remove item from cart
				tot_num--;// decrement the total number of items in cart
				tot_sum = tot_sum - pid[2].amt;// remove the amount from total sum
				removed[removed_count++] = 3; // add the id to the removed array
				oled_gotoXY(0, 0);// display related content on  screen
				oled_puts(" Product ID 3", &Font_7x10, 1);
				oled_gotoXY(0, 10);
				oled_puts(" REMOVED", &Font_7x10, 1);
				oled_gotoXY(0, 20);
				oled_puts(" - 80$", &Font_7x10, 1);
				oled_update_screen(); //display

			}
		} else if (strcmp(sNum, pid[3].tag_id) == 0) { // product id 4
			if ((pid[3].count == 0) || (pid[3].count % 2 == 0)) // count is even
					{
				pid[3].count++; // number of times id4  is scanned
				tot_num++;  //then add product count to cart
				tot_sum = tot_sum + pid[3].amt; // adds the amount of id 4 to total
				added[added_count++] = 4; // add id to keep track of added items
				oled_gotoXY(0, 0);// display related content on  screen
				oled_puts(" Product ID 4 ", &Font_7x10, 1);
				oled_gotoXY(0, 10);
				oled_puts(" ADDED", &Font_7x10, 1);
				oled_gotoXY(0, 20);
				oled_puts(" + 100$", &Font_7x10, 1);
				oled_update_screen(); //display
			} else if (pid[3].count % 2 != 0) // count is odd
					{ // when the same card is tapped again ,
				pid[3].count--; //then then remove item from cart
				tot_num--;// decrement the total number of items in cart
				tot_sum = tot_sum - pid[3].amt;// remove the amount from total sum
				removed[removed_count++] = 4;  // add the id to the removed array
				oled_gotoXY(0, 0);// display related content on  screen
				oled_puts(" Product ID 4", &Font_7x10, 1);
				oled_gotoXY(0, 10);
				oled_puts(" REMOVED", &Font_7x10, 1);
				oled_gotoXY(0, 20);
				oled_puts(" - 100$", &Font_7x10, 1);
				oled_update_screen(); //display

			}
		}
	}
	//keypad entry
	oled_gotoXY(0, 10);
	oled_puts("   Please enter   ", &Font_7x10, 1);
	oled_gotoXY(0, 20);
	oled_puts("from keypad:", &Font_7x10, 1);
	menu(); // displays menu
	oled_update_screen(); //display
	strcpy(received_string, key_input());


	if (strcmp(bill, received_string) == 0) {
		oled_gotoXY(0, 30);
		oled_puts("Display bill", &Font_7x10, 1);
		display_bill(); // function to display bill
		oled_gotoXY(0, 10);
		oled_clear_line();
		oled_gotoXY(0, 20);
		oled_clear_line();
		oled_update_screen(); //display
	} else if (strcmp(num, received_string) == 0) {
		oled_gotoXY(0, 30);
		oled_puts("Total items", &Font_7x10, 1);
		num_tot();
		oled_gotoXY(0, 10);
		oled_clear_line();
		oled_gotoXY(0, 20);
		oled_clear_line();
		oled_update_screen(); //display
	} else if (strcmp(sum, received_string) == 0) {
		oled_gotoXY(0, 30);
		oled_puts("Total amount", &Font_7x10, 1);
		sum_amt();
		oled_gotoXY(0, 10);
		oled_clear_line();
		oled_gotoXY(0, 20);
		oled_clear_line();
		oled_update_screen(); //display
	} else {
		oled_gotoXY(0, 30);
		oled_puts("Invalid entry", &Font_7x10, 1);
		oled_gotoXY(0, 10);
		oled_clear_line();
		oled_gotoXY(0, 20);
		oled_clear_line();
		oled_update_screen(); //display
	}
}
