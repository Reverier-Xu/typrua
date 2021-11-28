#!/bin/env python3

import os

folders = os.listdir('.')
files = []
for fpathe,dirs,fs in os.walk('.'):
  for f in fs:
    files.append(os.path.join(fpathe,f))

qrc_content_start = \
    '''<RCC>
        <qresource prefix="/">
    '''
qrc_content_end = \
    '''    </qresource>
    </RCC>
    '''

qrc_content = qrc_content_start

for file in files:
    qrc_content += f'        <file>{file[2:]}</file>\n'

qrc_content += qrc_content_end
print(qrc_content)

with open('main.qrc', 'w') as out:
    out.write(qrc_content)
