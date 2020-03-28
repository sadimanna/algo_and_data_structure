import matplotlib.pyplot as plt
import argparse as ap

parser = ap.ArgumentParser()
parser.add_argument('-f','--filename',required=True,help='Name of image file');
args = vars(parser.parse_args())

tree = plt.imread(args["filename"])
fig,ax = plt.subplots()
ax.imshow(tree)
ax.axis('off')
plt.show()
