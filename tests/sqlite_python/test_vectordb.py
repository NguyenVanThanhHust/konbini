from vectordb import VectorDB
import numpy as np

# Create random nd.array datasets
array1 = np.arange(10)
array2 = np.arange(10, 20)
array3 = np.arange(20, 30)

# Initialize the VectorDB class and create a collection name
db = VectorDB("students")
db.create()

# Insert the arrays into the database
db.insert([array1, array2, array3])

# Search for a specific value in the database
print(array1, array2, array3)
query = array2
print(query.shape)
output = db.search(query=query, num_results=1)

print(f"Results: {output}")

"""
Results: [0 1 2 3 4 5 6 7 8 9]
"""