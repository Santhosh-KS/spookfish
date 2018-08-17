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



import urllib.request
import urllib.parse
import validators


def SearchImage(imgPath):
  try:
    if validators.url(imgPath) == True:
      print('valid image path {}'.format(imgPath))
    else:
      print('Invalid image path {}'.format(imgPath))
      return

    imgSearchEngine = 'https://images.google.com/'
    imgSearchApi = 'searchbyimage?image_url='
    
    searchUrl = imgSearchEngine + imgSearchApi + imgPath
    #searchUrl = 'https://depositphotos.com/search/tom-cruise.html' 

    print('search URL: {}'.format(searchUrl))
    headers = {}
    headers['User-Agent'] = "Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.27 Safari/537.17"
    req = urllib.request.Request(searchUrl, headers = headers)
    resp = urllib.request.urlopen(req)
    respData = resp.read()
  
    #print(str(respData))
    saveFile = open('result.txt','w')
    saveFile.write(str(respData))
    saveFile.close()
  except Exception as e:
      print('SearchImage exception : {}'.format(str(e)))


#myImg = 'https://www.biography.com/.image/t_share/MTQ1MjI5NDUxNTc0MTI1OTc2/tom-hanks---early-years.jpg'
myImg = 'https://st.depositphotos.com/1694341/3667/i/950/depositphotos_36679759-stock-photo-tom-cruise.jpg'
#myImg = 'https://d3m9459r9kwism.cloudfront.net/img/examples/example-bec.jpg'
#myImg = 'https://storage.googleapis.com/sant-test-bucket/1.jpg'
SearchImage(myImg)
