db.createCollection("product_review");

// use product_review

// INSERT
db.product_review.insertOne({
    name: "OnePlus 9",
    price: 20000,
    categories: ["Electronics", "Mobiles"],
    reviews: [
        {
            rating: 10,
            reviewerName: "Abhishek",
            comments: ["Very nice", "Good"],
        },
        {
            rating: 7,
            reviewerName: "Hrishi",
            comments: ["Nice"],
        },
    ],
});
db.product_review.insertMany([
    {
        "name": "Samsung Galaxy S21",
        "price": 22000,
        "categories": ["Electronics", "Mobiles"],
        "reviews": [
            {
                "rating": 9,
                "reviewerName": "Sara",
                "comments": ["Impressive phone"]
            },
            {
                "rating": 8,
                "reviewerName": "Alex",
                "comments": ["Good features"]
            }
        ]
    }
    ,
    {
        "name": "Apple iPhone 13",
        "price": 25000,
        "categories": ["Electronics", "Mobiles"],
        "reviews": [
            {
                "rating": 9,
                "reviewerName": "John",
                "comments": ["Top-notch device"]
            },
            {
                "rating": 8,
                "reviewerName": "Linda",
                "comments": ["Smooth performance"]
            }
        ]
    }
    ,
    {
        "name": "Sony 4K Smart TV",
        "price": 18000,
        "categories": ["Electronics", "Televisions"],
        "reviews": [
            {
                "rating": 9,
                "reviewerName": "Mike",
                "comments": ["Great picture quality"]
            },
            {
                "rating": 7,
                "reviewerName": "Sarah",
                "comments": ["Good value for money"]
            }
        ]
    }
    ,
    {
        "name": "Dell Inspiron Laptop",
        "price": 1500,
        "categories": ["Electronics", "Laptops"],
        "reviews": [
            {
                "rating": 8,
                "reviewerName": "Tom",
                "comments": ["Solid performance"]
            },
            {
                "rating": 7,
                "reviewerName": "Laura",
                "comments": ["Decent laptop"]
            }
        ]
    }
    ,
    {
        "name": "Nikon D5600 DSLR Camera",
        "price": 700,
        "categories": ["Electronics", "Cameras"],
        "reviews": [
            {
                "rating": 8,
                "reviewerName": "Liam",
                "comments": ["Good for photography"]
            },
            {
                "rating": 6,
                "reviewerName": "Isabella",
                "comments": ["Average camera"]
            }
        ]
    }
    ,
    {
        "name": "Fiction Book: The Great Gatsby",
        "price": 15,
        "categories": ["Books", "Fiction"],
        "reviews": [
            {
                "rating": 9,
                "reviewerName": "Alice",
                "comments": ["A classic novel"]
            },
            {
                "rating": 8,
                "reviewerName": "Bob",
                "comments": ["Great storytelling"]
            }
        ]
    }
    ,
    {
        "name": "Sporting Goods: Tennis Racket",
        "price": 50,
        "categories": ["Sports", "Tennis"],
        "reviews": [
            {
                "rating": 9,
                "reviewerName": "David",
                "comments": ["Great for tennis enthusiasts"]
            },
            {
                "rating": 7,
                "reviewerName": "Sophie",
                "comments": ["Good quality"]
            }
        ]
    }
    ,
    {
        "name": "Men's Fashion: Leather Wallet",
        "price": 30,
        "categories": ["Fashion", "Accessories"],
        "reviews": [
            {
                "rating": 8,
                "reviewerName": "Mark",
                "comments": ["Stylish and functional"]
            },
            {
                "rating": 7,
                "reviewerName": "Linda",
                "comments": ["Good quality leather"]
            }
        ]
    }            
])

// FIND
db.product_review.find({})
db.product_review.findOne({})
db.product_review.findOne({name: 'OnePlus 9'})
db.product_review.find({}, {name: 1})
db.product_review.find({name: {$eq: 'OnePlus 9'}})
db.product_review.find({price: {$gte: 10000}})
db.product_review.find({"reviews.rating": {$gte: 5}})
db.product_review.find({"reviews.reviewerName": {$eq: 'Mark'}})
db.product_review.find({categories: {$in: ['Mobiles']}})
db.product_review.find({categories: {$all: ['Electronics', 'Mobiles']}})
db.product_review.find({$and: [{"reviews.rating": {$lte: 8}}, {price: {$lte: 10000}}] })
db.product_review.find({$or: [{"reviews.rating": {$lte: 8}}, {price: {$gte: 2000}}] })
db.product_review.find({}, {categories: {$slice: 1}})
db.product_review.find({}, {categories: {$slice: [0,1]}})
db.product_review.find({categories: {$size: 3}})    

// UPDATE
db.product_review.update({price: {$gte: 10000}}, {$set: {price: {$inc: 500}}}, {multi: true})
db.product_review.updateMany({price: {$gte: 10000}}, {$set: {price: {$inc: 500}}})
db.product_review.updateOne({"reviews.reviewerName": {$eq: 'Mark'}}, {$set: {price: 50}})
db.product_review.updateOne({"reviews.reviewerName": {$eq: 'Ashneer'}}, {$set: {name: 'Mac'}}, {upsert: true})
db.product_review.updateOne({"reviews.reviewerName": {$eq: 'Mark'}}, {$push: {categories: 'Television'}})

// DELETE
db.product_review.deleteOne({name: {$eq: 'Ashneer'}})
db.product_review.deleteMany({price: {$lte: 50}})

// UNWIND
db.product_review.aggregate([
    {$unwind: "$categories"}
])




