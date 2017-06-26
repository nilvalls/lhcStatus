from time import sleep
import urllib.request, io
from PIL import Image
from tesserocr import PyTessBaseAPI, PSM

URL = "https://vistar-capture.web.cern.ch/vistar-capture/lhc1.png"
filename = "lhc_status.txt"

while True:

    with urllib.request.urlopen(URL) as url:
        file = io.BytesIO(url.read())
        image = Image.open(file)

    with PyTessBaseAPI() as api:
        api.SetImage(image)
        api.SetRectangle(10, 40, image.size[0]-30, 40);
        api.SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ:")
        api.SetPageSegMode(PSM.SINGLE_LINE)
        status = api.GetUTF8Text().rstrip()
        with open(filename, 'a') as out:
            out.write(status + '\n')

    sleep(5)
