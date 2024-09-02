import os

SRC_DIR = './src'
OUTPUT_FILE = 'sources.mk'

def generate_sources():
    c_files = [file for file in os.listdir(SRC_DIR) if file.endswith('.c')]
    with open(OUTPUT_FILE, 'w') as f:
        f.write('SRC_FILES = ' + ' '.join([os.path.join(SRC_DIR, file) for file in c_files]) + '\n')

def main():
    generate_sources()
if __name__ == '__main__':
    main()
