from datetime import datetime
import instaloader
import re
import os
import sys

try:
    url = sys.argv[1]
except IndexError:
    print("\nCrie a pasta Insta Downloader dentro da sua pasta de Downloads\n\nInforme uma URL válida juntamente na execução do código.\nExemplo: python instadownloader.py URL\n")
    sys.exit()

downloadDir = 'D:/Usuários/Downloads/Insta Downloader'
os.chdir(downloadDir)

loader = instaloader.Instaloader(
   
  download_pictures=True, 
  download_videos=True,
  download_video_thumbnails=False, 
  download_geotags=False,
  download_comments=False, 
  save_metadata=False, 
  compress_json=False,
  filename_pattern='{profile}_{mediaid}'
  )

expr = r'\/p\/([^\/]*)/'
found = re.search(expr, url)

if found:
  print("Baixando ", found.group(1), "...")
  post = instaloader.Post.from_shortcode(loader.context, found.group(1))
  loader.download_post(post ,datetime.strftime(datetime.now(), '%d-%m-%Y-%H-%M-%S'))
  print("\n\nAquivo salvo na pasta Downloads\nInsta Downloader - By Pedro Tonidandel\n\n\n")