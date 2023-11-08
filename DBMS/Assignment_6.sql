-- 1] EXPLICIT CURSOR

CREATE TABLE Stud_Data(
    rollno INT,
    name VARCHAR(20)
);

CREATE TABLE New_Stud_Data(
    rollno INT,
    name VARCHAR(20)
);

INSERT INTO Stud_Data ()
VALUES
(1, 'John Smith'),
(2, 'Emily Johnson'),
(3, 'Michael Brown'),
(4, 'Sophia Wilson'),
(5, 'Daniel Lee'),
(6, 'Olivia Kim'),
(7, 'James Davis'),
(8, 'Ava Martinez'),
(9, 'William Rodriguez'),
(10, 'Emma Harris');

INSERT INTO New_Stud_Data ()
VALUES
(1, 'John Smith'),
(3, 'Michael Brown'),
(5, 'Daniel Lee'),
(6, 'Olivia Kim'),
(8, 'Ava Martinez'),
(11, 'Steve Smith'),
(12, 'Liam Johnson');

SET SQL_MODE = 'Oracle';

DELIMITER //

CREATE OR REPLACE PROCEDURE merge_data() AS
rollno INT;
name VARCHAR(20);
CURSOR cur IS SELECT * FROM New_Stud_Data;
BEGIN

    OPEN cur;
    FETCH cur INTO rollno, name;
    WHILE cur % FOUND LOOP
        FETCH cur INTO rollno, name;
        IF rollno NOT IN (SELECT rollno FROM Stud_Data WHERE Stud_Data.rollno = rollno AND Stud_Data.name = name) THEN
            INSERT INTO Stud_Data VALUES (rollno, name);
        END IF;
    END LOOP;
    CLOSE cur;
 
END;

//

DELIMITER ;

CALL merge_data()

SELECT *FROM Stud_Data;
SELECT *FROM New_Stud_Data;


