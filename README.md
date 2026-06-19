# Series Tracker

A lightweight, terminal-based C++ application to log and track your progress through book, manga, or anime series. It automatically saves your data to a CSV file so you never lose your progress.

## Features
*   **Track Progress:** Log total volumes versus volumes read with a visual progress bar.
*   **Persistent Storage:** Automatically loads from and saves to `series_data.csv`.
*   **CRUD Operations:** Easily add, display, edit, or delete series from your list.


## Data Format
The application reads and writes data to a file named `series_data.csv` in the same directory. The file uses the following format:
```csv
Naruto,72,45
One_Piece,105,105
```
*Note: Ensure your series names do not contain spaces when typing them into the terminal prompt to avoid input errors.*

## License
This project is open-source and free to use.
