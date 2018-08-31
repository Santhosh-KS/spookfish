import pafy
import os
from argparse import ArgumentParser

def GetCommandLineArgs():
    parser = ArgumentParser()
    parser.add_argument("-u", "--url", dest="url",
                    help="youtube URL",
                    metavar="URL")

    args = parser.parse_args()

    url= ''

    if not args.url:
      print('Invalid Command aruguments.')
      print('Usage:') 
      print('"python path.py -h" for more details')
      exit()
    else:
      url = args.url

    return url

URL = GetCommandLineArgs()

video = pafy.new(URL)
best = video.getbest(preftype="mp4")
print(best.url)
