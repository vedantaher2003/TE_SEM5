db.createCollection('students')

db.students.insertMany([
    {
        roll: 1,
        name: 'John Smith',
        grade: 'A',
        marks: 90
    },
    {
        roll: 2,
        name: 'Emily Johnson',
        grade: 'B',
        marks: 85
    },
    {
        roll: 3,
        name: 'Michael Brown',
        grade: 'C',
        marks: 92
    },
    {
        roll: 4,
        name: 'Sophia Wilson',
        grade: 'A',
        marks: 88
    },
    {
        roll: 5,
        name: 'Daniel Lee',
        grade: 'B',
        marks: 94
    },
    {
        roll: 6,
        name: 'Olivia Kim',
        grade: 'C',
        marks: 87
    },
    {
        roll: 7,
        name: 'James Davis',
        grade: 'A',
        marks: 91
    },
    {
        roll: 8,
        name: 'Ava Martinez',
        grade: 'B',
        marks: 86
    },
    {
        roll: 9,
        name: 'William Rodriguez',
        grade: 'C',
        marks: 89
    },
    {
        roll: 10,
        name: 'Emma Harris',
        grade: 'A',
        marks: 93
    }
])

var mapFunc = function (){
    emit(this.grade, this.marks);
};

var reduceFunc = function (key, values){
    return Array.sum(values);
};

db.students.mapReduce(
    mapFunc,
    reduceFunc,
    {out: "total_marks"}
);

db.total_marks.find();