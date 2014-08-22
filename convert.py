import random

# number of attributes
attrib = []

# 2000 instances
instance = []

# files
output_file = "digits_m.arff"
directory = "/vol/courses/comp422/datasets/mfeat-digits/"
file_set = ["mfeat-mor"] # only use morphological features
#file_set = ["mfeat-fac", "mfeat-fou", "mfeat-kar", "mfeat-mor", "mfeat-pix", "mfeat-zer"]

def load_matrix(dir, fname):
	f = open(dir+fname, "r")

	# fac 216 attributes * 2000
	# get the data into a matrix
	lines_list = f.readlines()
	data = [[float(val) for val in line.split()] for line in lines_list]

	print(len(data[0]))

	# @attribute name numeric
	for x in range( 0, len(data[0]) ):
		attrib.append("@attribute "+fname+"-"+str(x)+" numeric")


	if len(instance) == 0:
		for x in range( 0, len(data) ):
			instance.append([])

	for x in range( 0, len(data) ):
		for att in range( 0, len(data[x]) ):
			instance[x].append(str(data[x][att]))

def main():
	for fname in file_set:
		load_matrix(directory, fname)

	attrib.append("@attribute digit_type {0,1,2,3,4,5,6,7,8,9}")
	for classtype in range(0,10):
		for x in range(classtype*200,(classtype+1)*200):
			instance[x].append(str(classtype))


	out = open(output_file, "w")
	out.write("@relation digits\n")
	for s in attrib:
		out.write(s + "\n")

	out.write("@data\n")
	random.shuffle(instance)
	for s in instance:
		for v in s:
			out.write(v + " ")
		out.write("\n")


	

main()