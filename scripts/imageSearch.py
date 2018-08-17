'''
    MIT License

    Copyright (c) 2018 santhoshachar08@gmail.com

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE
    SOFTWARE.
'''


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
    #imagepath = 'https://www.biography.com/.image/t_share/MTQ1MjI5NDUxNTc0MTI1OTc2/tom-hanks---early-years.jpg'
    #imagepath =  'https://m.media-amazon.com/images/M/MV5BMTQ2MjMwNDA3Nl5BMl5BanBnXkFtZTcwMTA2NDY3NQ@@._V1_QL50_SY1000_CR0,0,691,1000_AL_.jpg'
    imagepath =  'http://www.gstatic.com/tv/thumb/persons/613075/613075_v9_ba.jpg'


  #googlepath = 'https://google.com/searchbyimage?image_url=' + imagepath
  googlepath = 'https://images.google.com/searchbyimage?image_url=' + imagepath

  sourceCode = opener.open(googlepath).read()

  #print(googlepath);
  #print(sourceCode)
  #<div class="tHqoQ rg_meta notranslate">{"cl":15,"cr":15,"id":"Ndslvd9iG03VSM:","oh":675,"ou":"https://www.biography.com/.image/t_share/MTQ1MjI5NDUxNTc0MTI1OTc2/tom-hanks---early-years.jpg","ow":1200,"
  #<div class="tHqoQ rg_meta  notranslate">{"cl":15,"cr":15,"id":"Ndslvd9iG03VSM:","oh":675,"ou"
  #findLinks = re.findall(r'<div class=".*?\srg_meta\s.*?">{"cl":.*?,"cr":.*?,"id":.*?,"oh":.*?,"ou":"(.*?)","ow":.*?',sourceCode)
  #findLinks = re.findall(r'<div class=".*?\ssrg_meta\s.*?">{.*?"id":.*?"ou":"(.*?)","ow":.*?',sourceCode)
  findLinks = re.findall(r'<dif class="tHqoQ rg_meta notranslate">.*?"ou":"(.*?)","ow":.*?', sourceCode);


  for eachThing in findLinks:
      print(eachThing)


imageLookup()
