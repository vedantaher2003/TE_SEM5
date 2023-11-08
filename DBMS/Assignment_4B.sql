-- CODE BLOCK TO CALCULATE AREA OF CIRCLE FOR RADIUS VARYING FROM 5-9

CREATE TABLE Data (
radius INT PRIMARY KEY,
area FLOAT
);

-- !! IMPORTANT - BELOW ALL BLOCK OF CODES ARE SUBJECT TO WORK ONLY IF ORACLE MODE IS SET
-- SYNTAX FOR PURE MARIADB IS DIFFERENT THAN THE ORACLE MODE
SET SQL_MODE = 'Oracle';

-- 1] UNNAMED BLOCK 

DELIMITER //
DECLARE 
area FLOAT;
pii FLOAT;
BEGIN
    SET pii = 3.14;
    FOR I IN 5..9 LOOP
        SET area = I * I * pii;
        INSERT INTO Data VALUES (I, area);
    END LOOP;
END;
//

DELIMITER ;
SELECT *FROM Data;


-- 2] PROCEDURE

DELIMITER //

CREATE OR REPLACE PROCEDURE cal_area() AS
area FLOAT;
pii FLOAT;
BEGIN
    SET pii = 3.14;
    FOR I IN 5..9 LOOP
        SET area = I * I * pii;
        INSERT INTO Data VALUES (I, area);
    END LOOP;
END;
//

DELIMITER ;
CALL cal_area();
SELECT *FROM Data;


-- 3] FUNCTION

DELIMITER //

CREATE OR REPLACE FUNCTION cal_area_func(radius INT) 
RETURN FLOAT
AS
area FLOAT;
pii FLOAT;
BEGIN
    SET pii = 3.14;
    SET area = pii * radius * radius;
    RETURN area;
END;

//

CREATE or REPLACE PROCEDURE cal_area_proc() AS
area FLOAT;
BEGIN
    FOR I IN 5..9 LOOP
        SET area = cal_area_func(I);
        INSERT INTO Data VALUES (I, area);
    END LOOP;
END;
//

DELIMITER ;
CALL cal_area_proc();
SELECT *FROM Data;