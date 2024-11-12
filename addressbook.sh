#!/bin/bash

ADDRESS_BOOK="address_book.txt"

create_address_book() {
    if [[ -f $ADDRESS_BOOK ]]; then
        echo "Address book already exists."
    else
        > $ADDRESS_BOOK
        echo "Address book created."
    fi
}

view_address_book() {
    if [[ ! -s $ADDRESS_BOOK ]]; then
        echo "Address book is empty."
    else
        echo "Address Book:"
        cat $ADDRESS_BOOK
    fi
}

insert_record() {
    echo "Enter Name:"
    read name
    echo "Enter Phone Number:"
    read phone
    echo "Enter Email:"
    read email
    echo "$name, $phone, $email" >> $ADDRESS_BOOK
    echo "Record added."
}

delete_record() {
    echo "Enter the Name of the record to delete:"
    read name
    if grep -q "^$name," $ADDRESS_BOOK; then
        grep -v "^$name," $ADDRESS_BOOK > temp && mv temp $ADDRESS_BOOK
        echo "Record deleted."
    else
        echo "Record not found."
    fi
}

search_modify_record() {
    echo "Enter the Name of the record to search:"
    read name
    if grep -q "^$name," $ADDRESS_BOOK; then
        grep "^$name," $ADDRESS_BOOK
        echo "Do you want to modify this record? (yes/no)"
        read choice
        if [[ "$choice" == "yes" ]]; then
            delete_record
            echo "Enter new Name:"
            read new_name
            echo "Enter new Phone Number:"
            read new_phone
            echo "Enter new Email:"
            read new_email
            echo "$new_name, $new_phone, $new_email" >> $ADDRESS_BOOK
            echo "Record updated."
        fi
    else
        echo "Record not found."
    fi
}

while true; do
    echo "Choose an option:"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert a Record"
    echo "4. Delete a Record"
    echo "5. Search and Modify a Record"
    echo "6. Exit"
    read choice
    case $choice in
        1) create_address_book ;;
        2) view_address_book ;;
        3) insert_record ;;
        4) delete_record ;;
        5) search_modify_record ;;
        6) echo "Exiting."; exit ;;
        *) echo "Invalid option. Please try again." ;;
    esac
done
