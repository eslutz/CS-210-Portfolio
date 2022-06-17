"""
Eric Slutz
CS-210
Project 3

Python Functions
"""


class InventoryItem:
    """InventoryItem class for describing an item that was sold."""
    def __init__(self, name, qty=1):
        """Constructor for InventoryItem, sets item name and quantity sold (defaults to 1 item sold)."""
        self.name = name
        self.quantity = int(qty)

    def increment_quantity(self):
        """Function for incrementing the quantity that was sold of an item."""
        self.quantity += 1


class Inventory:
    """Inventory class for storing a list of InventoryItems sold."""
    def __init__(self):
        """Constructor initializes and empty list."""
        self.inventory_list = []

    def __getitem__(self, item):
        """Getter for item in the list."""
        return item

    def check_for_item(self, item_name):
        """
        Checks by item name if the item is already in the list.

        :param item_name: name of the item to check list for.
        :return: index of the item, -1 if item not found.
        """
        # Checks if the item is already in the list.
        for item_index, item in enumerate(self.inventory_list):
            # If the item is in the list, break our of the loop, retaining the index of the item.
            if item.name.lower() == item_name.lower():
                break
        # Otherwise set index to -1, representing the item is not currently in the list.
        else:
            item_index = -1
        # Return the items index.
        return item_index

    def add_item_by_name(self, item_name):
        """
        Adds an item to the list given the item name.

        :param item_name: name of the item to add to list.
        """
        # Checks if the item is already in the list.
        item_index = self.check_for_item(item_name)

        # If item is not already in the list, create a new InventoryItem and add it to the list.
        if item_index == -1:
            self.inventory_list.append(InventoryItem(item_name.title()))
        # Otherwise, the item is in the list, so increment the item's quantity by one.
        else:
            self.inventory_list[item_index].increment_quantity()

    def add_item(self, new_item):
        """
        Add an InventoryItem to the list.

        :param new_item: item to add to list.
        """
        # Checks if the item is already in the list.
        item_index = self.check_for_item(new_item.name)

        # If item is not already in the list, add it to the list.
        if item_index == -1:
            self.inventory_list.append(new_item)
        # Otherwise, the item is in the list, so increment the item's quantity by one.
        else:
            self.inventory_list[item_index].increment_quantity()


def open_file(input_file):
    """
    Attempts to open a file.

    :param input_file: name & path of the file to open.
    :return: lines from the file
    """

    # Try to open a file.
    try:
        # Read in items sold from input file.
        with open(input_file, 'r') as file:
            lines = file.readlines()
    # Catch any exception opening file.
    except OSError:
        raise Exception("Unable to open file to read")
    else:
        # Return lines from file.
        return lines


def get_inventory(input_file, output_file):
    """
    Gets items sold from a file and adds them to inventory list with quantity of each item sold.

    :param input_file: name & path of the file to open.
    :param output_file: name & path of the file to save.
    :return: break out of function if file cannot be saved.
    """
    # Create inventory list.
    inventory = Inventory()

    # Attempt to get data from a file.
    try:
        # Call function to open a file and read in the data.
        lines = open_file(input_file)
    # Catch any exceptions, display error message, and break out of function.
    except Exception as ex:
        print(ex)
        return

    # For each item, add it to the inventory list.
    for line in lines:
        inventory.add_item_by_name(line.strip())

    # Try to open a file to write to.
    try:
        # Write the inventory items and quantities to a file.
        with open(output_file, 'w') as file:
            for item in inventory.inventory_list:
                file.write('{} {}'.format(item.name, item.quantity))
                file.write('\n')
    # Catch any exception opening file, display error message, and break out of function.
    except OSError:
        print("Unable to open file to write")
        return


def display_inventory(input_file):
    """
    Print out the name of the items sold and the quantity of each item sold

    :param input_file: name & path of the file to open.
    :return: break out of function if file cannot be saved.
    """
    # Declare variable for storing length of the longest item name for formatting output.
    max_item_name_length = 0
    # Create inventory list.
    inventory = Inventory()

    # Attempt to get data from a file.
    try:
        # Call function to open a file and read in the data.
        lines = open_file(input_file)
    # Catch any exceptions, display error message, and break out of function.
    except Exception as ex:
        print(ex)
        return

    # Loop through each item in the list.
    for line in lines:
        # Split line into item name and quantity of the item sold.
        item = line.split(' ')
        name, qty = [value.strip() for value in item]
        # Find the length of the longest item name.
        if max_item_name_length < len(name):
            max_item_name_length = len(line.strip())
        # Create a new item from the line input.
        item = InventoryItem(name, qty)
        # Add the item to the inventory list.
        inventory.add_item(item)

    # Add some buffer to the max size.
    max_item_name_length += 8
    # Loop through and display each item from the list.
    for item in inventory.inventory_list:
        print('Item: {}'.ljust(max_item_name_length - len(item.name)).format(item.name),
              'Quantity: {}'.format(item.quantity))


def get_item_qty(input_file, item_name):
    """
    Searches the list of items sold for a specific item and returns how many of that item were sold.

    :param input_file: name & path of the file to open.
    :param item_name: name of the item to search list for.
    :return: how many of the item were sold, 0 if item not in the list (none were sold).
    """
    # Create inventory item.
    inventory = Inventory()

    # Call function to open a file and read in the data.
    lines = open_file(input_file)

    # For each item, add it to an inventory list.
    for line in lines:
        # Split line into item name and quantity of the item sold.
        item = line.strip().split(' ')
        name, qty = [value.strip() for value in item]
        # Create a new item from the line input.
        item = InventoryItem(name, qty)
        # Add the item to the inventory list.
        inventory.add_item(item)

    # Loop through each item in the inventory list.
    for item in inventory.inventory_list:
        # Check if item is in the list.
        if item.name.lower() == item_name.lower():
            # If it is, return the quantity of the item sold.
            return item.quantity
    # Otherwise, none of the item were sold, so return 0.
    else:
        return 0
