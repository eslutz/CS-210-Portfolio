"""
Eric Slutz
CS-210
Project 3

Python Functions
"""


class InventoryItem:
    def __init__(self, name, qty=1):
        self.name = name
        self.quantity = int(qty)

    def increment_quantity(self):
        self.quantity += 1


class Inventory:
    def __init__(self):
        self.inventory_list = []

    def __getitem__(self, item):
        return item

    def add_item_by_name(self, item_name):
        for item_index, item in enumerate(self.inventory_list):
            if item.name == item_name:
                break
        else:
            item_index = -1

        if item_index == -1:
            self.inventory_list.append(InventoryItem(item_name.title()))
        else:
            self.inventory_list[item_index].increment_quantity()

    def add_item(self, new_item):
        for item_index, item in enumerate(self.inventory_list):
            if item.name.lower() == new_item.name.lower():
                break
        else:
            item_index = -1

        if item_index == -1:
            self.inventory_list.append(new_item)
        else:
            self.inventory_list[item_index].increment_quantity()


def get_inventory(input_file, output_file):
    # Create inventory item.
    inventory = Inventory()

    # Read in items sold from input file.
    with open(input_file, 'r') as file:
        lines = file.readlines()
    # For each item, add it to the inventory list.
    for line in lines:
        inventory.add_item_by_name(line.strip())
    # Write the inventory items and quantities to a file.
    with open(output_file, 'w') as file:
        for item in inventory.inventory_list:
            file.write('{} {}'.format(item.name, item.quantity))
            file.write('\n')


def display_inventory(input_file):
    max_item_name_length = 0
    inventory = Inventory()

    # Read in items sold from input file.
    with open(input_file, 'r') as file:
        lines = file.readlines()

    # For each item, print out name and quantity.
    for line in lines:
        item = line.split(' ')
        name, qty = [value.strip() for value in item]
        if max_item_name_length < len(name):
            max_item_name_length = len(line.strip())
        item = InventoryItem(name, qty)
        inventory.add_item(item)

    max_item_name_length += 8
    for item in inventory.inventory_list:
        print('Item: {}'.ljust(max_item_name_length - len(item.name)).format(item.name), 'Quantity: {}'.format(item.quantity))


def get_item_qty(input_file, item_name):
    # Create inventory item.
    inventory = Inventory()

    # Read in items sold from input file.
    with open(input_file, 'r') as file:
        lines = file.readlines()

    # For each item, add it to an inventory list.
    for line in lines:
        item = line.strip().split(' ')
        name, qty = [value.strip() for value in item]
        item = InventoryItem(name, qty)
        inventory.add_item(item)

    for item in inventory.inventory_list:
        if item.name.lower() == item_name.lower():
            return item.quantity
    else:
        return 0
