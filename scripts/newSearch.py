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


myImg = 'https://www.biography.com/.image/t_share/MTQ1MjI5NDUxNTc0MTI1OTc2/tom-hanks---early-years.jpg'
#myImg = 'https://d3m9459r9kwism.cloudfront.net/img/examples/example-bec.jpg'
#myImg = 'https://storage.googleapis.com/sant-test-bucket/1.jpg'
SearchImage(myImg)
