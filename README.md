# Ticket Monster

Ticket Monster is a simple ticket management application that organizes tickets based on priority.

## Features

- Add new tickets
- Assign priorities to tickets
- View the highest-priority ticket
- Remove completed tickets
- Keep tickets ordered by priority
- Save ticket data to a text file
- Load saved tickets when the program starts

## Data Structure

The application uses a **binary heap** to implement a priority queue. This allows the highest-priority ticket to be accessed efficiently.

## Persistent Storage

Ticket information is stored in a simple `.txt` file so that ticket data is preserved after the application is closed.

## Purpose

The purpose of Ticket Monster is to demonstrate the use of a non-linear data structure in a practical ticket-management system.