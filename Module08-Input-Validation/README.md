# Module 08 - Input Validation & Protecting Data

Added validation to addRecord() so it no longer accepts bad input. The date must match YYYY-MM-DD (checked by a new isValidDate() function), the category cannot be empty, and the amount must be a positive number (checked by a new getValidAmount() function adapted from the class example). Each check loops with a clear error message until the user enters something valid, instead of crashing or silently accepting bad data.
