"""
Demo of the histogram (hist) function with a few features.

In addition to the basic histogram, this demo shows a few optional features:

    * Setting the number of data bins
    * The ``normed`` flag, which normalizes bin heights so that the integral of
      the histogram is 1. The resulting histogram is a probability density.
    * Setting the face color of the bars
    * Setting the opacity (alpha value).

"""
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
from lxml import etree
import os
import sys


def Plot( InputFileName ):
		
	Datafilename, InputExtension = os.path.splitext(InputFileName);

	doc = etree.parse(InputFileName)
    RgnType = ["WORN", "DRAG", "PERSON"]
    
    for Type in RgnType:
    
    	vals = doc.find(Type);
    	x = np.fromstring(vals.text, dtype=float, sep="\n");
    	xMean = np.mean(x)
    	xStd			= np.std(x)
    	xMin			= np.min(x)
    	xMax 	  = np.max(x)
    
    	print "XMean " +  str(xMean)
    	print "XStd " + str(xStd)
    
    
    	num_bins = 100
    	# the histogram of the data
    	n, bins, patches = plt.hist(x, num_bins, normed=0, facecolor='green', alpha=0.5)
    
    	# Tweak spacing to prevent clipping of ylabel
    	plt.subplots_adjust(left=0.15)
    
    	y = mlab.normpdf(bins, xMean, xStd)
    	  
    	plt.plot(bins,y, 'r--') 
    
    	l = plt.axvline(x= xMean, linestyle='-.', linewidth=2)
    	p = plt.axvspan(xMean - xStd, xMean + xStd, facecolor='r', alpha=0.2)
    
    	plt.xlabel('Samples')
    	plt.ylabel('Normalized Counts')
    	plt.title('Histogram of Probabilities')
    
    	minAnnot = ' min \n' + str("%0.3f" % xMin);
    	#plt.annotate( minAnnot, xy=(xMin, n[0]), xytext=(xMin - xMin/10, n[0] + n[0] * 0.1), arrowprops=dict(arrowstyle="->"))
    	plt.text( xMin, n[0], minAnnot);
    
    	nSize = np.size(n)
    	maxAnnot = ' max \n' + str("%0.3f " % xMax);
    	YMax = n[nSize - 1]
    	#plt.annotate( maxAnnot, xy=(xMax, YMax),  arrowprops=dict(arrowstyle="->"))
    	plt.text( xMax, YMax, maxAnnot)
    
    	nMean = np.mean(n)
    	nMax  = np.max(n)
    
    	meanAnnot  = '$\mu = $' + str("%0.3f " % xMean)
    	#plt.annotate( meanAnnot, xy=(xMean, nMax ), xytext=(xMean - xStd, nMax + nMax/10), arrowprops=dict(arrowstyle="->") )
    	#plt.text( xMean, nMax, meanAnnot)
    
    	# Draw Line
    	plt.arrow(xMean, nMax, xStd, 0, alpha=0.5, length_includes_head=True, shape='full')
    	stdAnnot = '$\sigma = $' + str("%0.3f" % xStd)
    	#plt.annotate( stdAnnot, xy=((xMean + xStd)/2, nMax ), xytext=((xMean + xStd)/2, nMax - nMax/10), arrowprops=dict(arrowstyle="->") )
    	#plt.text(xMean + xStd , nMax, stdAnnot )
    
    	commonText = meanAnnot + "\n" + stdAnnot;
    	plt.text( xMean, nMax, commonText)
    
    	plt.grid(color='black', linestyle='--', linewidth=1, alpha=0.1)
    	plt.ylim([0, nMax + nMax * 0.2 ])
    
    	plt.savefig( Datafilename + ".pdf")
    	#plt.show()
	
	plt.close()



print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)

InputFileName = ""

if( len(sys.argv) < 2 ):
	print "Path to datafile missing"
	print "Using default fileNames"
	print "InputFileName: Dist.xml"
	InputFileName = "Dist.xml";
	
else:
	
	for i in range( 1,  len(sys.argv) ):
		InputFileName = sys.argv[i]		
		Plot( InputFileName )




