db.createCollection("products"); 

db.products.insertMany([
        {
            productName: "Product A",
            price: 29.99,
            rating: 4.5,
            qty: 100,
            categories: ["Electronics", "Gadgets"]
        },
        {
            productName: "Product B",
            price: 19.99,
            rating: 4.0,
            qty: 50,
            categories: ["Home & Kitchen", "Appliances"]
        },
        {
            productName: "Product C",
            price: 49.99,
            rating: 4.7,
            qty: 75,
            categories: ["Clothing", "Fashion"]
        },
        {
            productName: "Product D",
            price: 39.99,
            rating: 4.2,
            qty: 30,
            categories: ["Toys", "Games"]
        },
        {
            productName: "Product E",
            price: 59.99,
            rating: 4.8,
            qty: 120,
            categories: ["Sports", "Fitness"]
        },
        {
            productName: "Product F",
            price: 12.99,
            rating: 3.9,
            qty: 20,
            categories: ["Books", "Education"]
        },
        {
            productName: "Product G",
            price: 69.99,
            rating: 4.6,
            qty: 60,
            categories: ["Beauty", "Skincare"]
        },
        {
            productName: "Product H",
            price: 34.99,
            rating: 4.4,
            qty: 45,
            categories: ["Food", "Groceries"]
        },
        {
            productName: "Product I",
            price: 22.99,
            rating: 4.1,
            qty: 15,
            categories: ["Automotive", "Accessories"]
        },
        {
            productName: "Product J",
            price: 64.99,
            rating: 4.9,
            qty: 90,
            categories: ["Furniture", "Home Decor"]
        }
])

db.products.aggregate([ {$group: {_id: '$productName'}} ])

db.products.aggregate([ {$group: {_id: '$productName', qty: {$sum: '$qty'} }} ])

db.products.aggregate([ {$limit: 1} ])

db.products.aggregate([ {$project: {projectName: 1, qty: 1}} ])

db.products.aggregate([ {$sort: {qty: -1}} ])

db.products.aggregate([ {$match: {productName: 'Product A'}} ])

db.products.aggregate([ {$count: 'total_products_qty'} ])

db.products.distinct('productName')

db.products.createIndex({productName: 1})

db.products.createIndex({productName: 1, rating: 1})

db.products.createIndex({productName: 1}, {unique: true})

db.products.find().explain('executionStats')