--- BORROWER AND FINE PROBLEM STATEMENT

CREATE TABLE Borrower (
    roll_no INT,
    name VARCHAR(20),
    doi DATE,
    book_name VARCHAR(100),
    status VARCHAR(10)
);

CREATE TABLE Fine(
    roll_no INT,
    dor DATE,
    amount INT
);



-- 1] PROCEDURE (TAKE DOR FROM PROCEDURE)

SET SQL_MODE = 'Oracle';

DELIMITER //

CREATE OR REPLACE PROCEDURE cal_fine(roll_no INT, book_name VARCHAR(100), dor DATE) AS
days INT;
BEGIN
    SELECT DATEDIFF(dor, Borrower.doi) INTO days FROM Borrower WHERE Borrower.roll_no = roll_no AND Borrower.book_name = book_name;
    IF days > 15 AND days < 30 THEN
        INSERT INTO Fine VALUES (roll_no, dor, (days-15)*5);
    ELSIF days > 30 THEN
        INSERT INTO Fine VALUES (roll_no, dor, (days-30)*50 + 15*5);
    END IF;
    UPDATE Borrower SET status = 'Returned' WHERE Borrower.roll_no = roll_no AND Borrower.book_name = book_name;
END;

//

DELIMITER ;

CALL cal_fine(31109, 'Oops', '2022-05-23');



-- 2] PROCEDURE (WITH CURR_DATE AS RETURN DATE)

SET SQL_MODE = 'Oracle';

DELIMITER //

CREATE OR REPLACE PROCEDURE cal_fine(roll_no INT, book_name VARCHAR(100)) AS
days INT;
BEGIN
    SELECT DATEDIFF(CURDATE(), Borrower.doi) INTO days FROM Borrower WHERE Borrower.roll_no = roll_no AND Borrower.book_name = book_name;
    IF days > 15 AND days < 30 THEN
        INSERT INTO Fine VALUES (roll_no, CURDATE(), (days-15)*5);
    ELSIF days > 30 THEN
        INSERT INTO Fine VALUES (roll_no, CURDATE(), (days-30)*50 + 15*5);
    END IF;
    UPDATE Borrower SET status = 'Returned' WHERE Borrower.roll_no = roll_no AND Borrower.book_name = book_name;
END;

//

DELIMITER ;

CALL cal_fine(31109, 'Oops');
