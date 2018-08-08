#import pysftp as sftp
import urllib2
from urllib2 import urlopen
from cookielib import CookieJar
import re
import time

cj = CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
opener.addheaders =  [('User-Agent', 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.0 Safari/537.36')]


def imageLookup():
  '''
  s = sftp.Connection(host="pythonprogramming.net",
                      username = "python",
					  password = "rules")
  localpath = "path_to_image"
  numToAdd = str(int(time.time()))
  remotepath = '/var/www/imagerec/currentImage'+numToAdd+'.jpg'
  s.put(localpath, remotepath)
  s.close()
  '''
  #imagepath = 'http://pythonprogramming.net/imagerec/currentImage'+numToAdd+'.jpg'
  imagepath = 'https://www.biography.com/.image/t_share/MTQ1MjI5NDUxNTc0MTI1OTc2/tom-hanks---early-years.jpg'

  
  #googlepath = 'https://google.com/searchbyimage?image_url=' + imagepath
  googlepath = 'https://images.google.com/searchbyimage?image_url=' + imagepath
  
  sourceCode = opener.open(googlepath).read()
  
  
  #print(sourceCode)
  #<div class="tHqoQ rg_meta notranslate">{"cl":15,"cr":15,"id":"Ndslvd9iG03VSM:","oh":675,"ou":"https://www.biography.com/.image/t_share/MTQ1MjI5NDUxNTc0MTI1OTc2/tom-hanks---early-years.jpg","ow":1200,"
  #<div class="tHqoQ rg_meta  notranslate">{"cl":15,"cr":15,"id":"Ndslvd9iG03VSM:","oh":675,"ou"
  findLinks = re.findall(r'<div class=".*?\srg_meta\s.*?">{"cl":.*?,"cr":.*?,"id":.*?,"oh":.*?,"ou":"(.*?)","ow":.*?',sourceCode)
  #findLinks = re.findall(r'<div class=".*?rg_meta.*?">{"cl":".*?","cr":.*?,"id":.*?,"oh":.*?,"ou":"(.*?)",.*?',sourceCode) 
  #findLinks = re.findall(r'<div class=".*?rg_meta">{"os":".*?","cb":.*?,"ou":(.*?),"rh":"', sourceCode)
  #findLinks = re.findall(r'<div class="(.*?)</div>', sourceCode)

  
  for eachThing in findLinks:
    print(eachThing)
  
  
imageLookup()
