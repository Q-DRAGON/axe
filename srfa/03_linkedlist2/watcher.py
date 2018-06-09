import os
import sys
import time
import logging
from watchdog.observers import Observer
from watchdog.events import LoggingEventHandler
from watchdog.events import FileSystemEventHandler


def auto_test(path):
    suffix = path.split('.')[-1]
    if suffix == 'py':
        cmd = 'nosetests -s'
        os.system(cmd)


# 自定义事件处理类
class watcher(FileSystemEventHandler):
    def __init__(self, *args, **kwargs):
        FileSystemEventHandler.__init__(self, *args, **kwargs)
        print('watcher init', *args, **kwargs)

    # def on_any_event(self, event):
    #     print('watcher on_any_event',)

    def on_modified(self, event):
        print('watcher on_modified',)
        auto_test(event.src_path)

    # def on_moved(self, event):
    #     print('watcher on_moved',)

    # def on_deleted(self, event):
    #     print('watcher on_deleted',)

    # def on_created(self, event):
    #     print('watcher on_created',)


def main():
    config = dict(
        level=logging.INFO,
        format='%(asctime)s - %(message)s',
        datefmt='%Y-%m-%d %H:%M:%S',
    )
    logging.basicConfig(**config)
    event_handler = watcher()
    observer = Observer()
    path = '.'
    observer.schedule(event_handler, path, recursive=True)
    observer.start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()


if __name__ == "__main__":
    main()
