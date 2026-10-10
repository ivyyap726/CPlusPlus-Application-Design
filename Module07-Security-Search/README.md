# Module 07 - Security, Roles & Binary Search

Introduced a User base class with Admin and RegularUser subclasses to add role-based permissions. Each transaction now gets a unique auto-incremented ID, which keeps the record list sorted by ID so it can be searched with a binarySearchByID() function adapted from the class example. Added a deleteRecord() function, and restricted Add Record and Delete Record to Admins only, while Regular Users can still view, search, and view the summary.
