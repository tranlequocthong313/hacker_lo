import os
import threading

def create_file(file_number):
    file_path = f"/mnt/nvme0n1p5/Workspace/du_an_hacker_lo/tests/file{file_number}.txt"
    with open(file_path, "w") as file:
        string="Hello, world!"*10000
        file.write(string)
    print(f"Created file: {file_path}")

def create_files(num_files, num_threads):
    files_per_thread = num_files // num_threads
    remaining_files = num_files % num_threads

    threads = []
    file_number = 1

    for _ in range(num_threads):
        if remaining_files > 0:
            thread_files = files_per_thread + 1
            remaining_files -= 1
        else:
            thread_files = files_per_thread

        thread = threading.Thread(target=create_file, args=(file_number,))

        threads.append(thread)
        thread.start()

        file_number += thread_files

    for thread in threads:
        thread.join()

num_files = 1000000
num_threads = 5

create_files(num_files, num_threads)

