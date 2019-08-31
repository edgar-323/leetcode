
def fact1(n):
	prod = 1
	while (n > 0):
		prod *= n
		n -= 1
	return prod

def doubleListSize(arr):
	newArr = list()
	for i in range(2 * len(arr)):
		if (i < len(arr)):
			newArr.append(arr[i])
		else:
			newArr.append(0)
	return newArr;

def fact2(n):
	a = list([0])
	a[0] = 1
	size = 1 		#size of a[]

	carry = 0

	for num in range(1, n+1):

		for j in range(0, size):
			x = a[j]*num + carry
			a[j] = x % 10
			carry = x // 10

		while (carry > 0):
			if (size >= len(a)):
				a = doubleListSize(a)
			a[size] = carry % 10
			carry //= 10
			size += 1

	a = a[:size]
	a.reverse()
	return a

def print1(n):
	print(fact1(n))

def print2(n):
	arr = fact2(n)
	num = str()
	for digit in arr:
		num += str(digit)
	print(num)

def test(n):
	print1(n)
	print2(n)

for i in [5 * j for j in range(10)]:
	print("Factorial(" + str(i) + "):")
	test(i)
	print("\n")
