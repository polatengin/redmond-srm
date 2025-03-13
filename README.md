# Secure Remove (srm)

## Overview

This project demonstrates how a secure remove (`srm`) command can be implemented. Unlike the normal `rm` command, which deletes files immediately, `srm` moves files to a recycle bin, allowing them to be restored later if needed.

## Features

- **Move to Recycle Bin**: Files are moved to a `/recycle/` directory instead of being deleted immediately.
- **Restore Files**: Deleted files can be restored to their original locations.
- **List Deleted Files**: View a list of files currently in the recycle bin.
- **Purge Recycle Bin**: Permanently delete all files in the recycle bin.

## Implementation Details

- **Recycle Bin**: The project creates a `/recycle/` folder in the root directory. All deleted files are moved to this folder.
- **Metadata**: A metadata file (`/recycle/.metadata`) stores the original paths of the deleted files, allowing them to be restored later.

## Usage

To use the `srm` command, you can perform various operations such as moving files to the recycle bin, listing deleted files, restoring files, and purging the recycle bin.

### Commands

- `srm <file/folder> [file/folder] ...`: Move the specified files or folders to the recycle bin.
- `srm --list`: List all deleted files in the recycle bin.
- `srm --restore <file>`: Restore a specific file from the recycle bin.
- `srm --restore-all`: Restore all files from the recycle bin.
- `srm --purge`: Permanently delete all files in the recycle bin.

### Examples

- Move a file to the recycle bin:
  ```sh
  srm myfile.txt
  ```

- Move more than one file to the recycle bin:
  ```sh
  srm myfile.txt myfile2.txt myfile3.txt
  ```

- List deleted files:
  ```sh
  srm --list
  ```

- Restore a specific file:
  ```sh
  srm --restore myfile.txt
  ```

- Restore all files:
  ```sh
  srm --restore-all
  ```

- Purge the recycle bin:
  ```sh
  srm --purge
  ```

## Building the Project

To build the project, run the following commands:

```sh
make
```

This will compile the source files and create the `srm` executable in the `./dist` directory.
