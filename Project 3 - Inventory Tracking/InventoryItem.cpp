/**
 * Eric Slutz
 * CS-210
 * Project 3
 *
 * Inventory Item Class
 */

#include "InventoryItem.h"

/**
 * Constructor for an Inventory Item.
 *
 * @param name the name of the item.
 * @param qty how many of that item was sold.
 */
InventoryItem::InventoryItem(const string& name, int qty) {
	this->name = name;
	this->quantity = qty;
}

/**
 * Getter for item name.
 *
 * @return items name.
 */
string InventoryItem::getName() {
	return name;
}

/**
 * Getter for quantity of item sold.
 *
 * @return quantity of item sold
 */
int InventoryItem::getQty() const {
	return quantity;
}
