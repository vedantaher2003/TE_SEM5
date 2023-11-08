-- NAMED PROC TO CAL GRADE OF STUDENTS FROM MARKS

CREATE TABLE stud_marks(
    roll_no INT PRIMARY KEY,
    name VARCHAR(20),
    total_marks INT
);

CREATE TABLE stud_grades(
    roll_no INT PRIMARY KEY,
    name VARCHAR(20),
    grade VARCHAR(25)
);



-- 1] NAMED PROCEDURE

SET SQL_MODE = 'Oracle';

DELIMITER //

CREATE OR REPLACE PROCEDURE proc_cal_grade(roll_no INT) AS
name VARCHAR(20);
total_marks INT;
grade VARCHAR(25);
BEGIN
    SELECT stud_marks.name, stud_marks.total_marks INTO name, total_marks FROM stud_marks WHERE stud_marks.roll_no = roll_no;
    IF total_marks<=1500 AND total_marks>=990 THEN
        SET grade = 'Distinction';
    ELSIF total_marks<=989 AND total_marks>=900 THEN
        SET grade = 'First Class';
    ELSIF total_marks<=899 AND total_marks>=825 THEN
        SET grade = 'Higher Second Class';
    END IF;
    INSERT INTO stud_grades VALUES (roll_no, name, grade);
END;

//

DELIMITER ;
CALL proc_cal_grade(1);
SELECT *FROM stud_grades;



-- 2] NAMED FUNCTION

SET SQL_MODE = 'Oracle';

DELIMITER //

CREATE OR REPLACE FUNCTION func_cal_grade(marks INT) 
RETURN VARCHAR(25)
AS
grade VARCHAR(25);
BEGIN
    IF marks<=1500 AND marks>=990 THEN
        SET grade = 'Distinction';
    ELSIF marks<=989 AND marks>=900 THEN
        SET grade = 'First Class';
    ELSIF marks<=899 AND marks>=825 THEN
        SET grade = 'Higher Second Class';
    END IF;
    RETURN grade;
END;

//

DELIMITER ;
SELECT roll_no, name, func_cal_grade(total_marks) FROM stud_marks;
