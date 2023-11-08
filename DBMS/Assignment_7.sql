-- TRIGGERS

CREATE TABLE Library(
    book_name VARCHAR(100),
    shelf_no INT
);

CREATE TABLE Library_Audit(
    book_name VARCHAR(100),
    shelf_no INT,
    action VARCHAR(20)
);

INSERT INTO Library VALUES
('Doglapan', 10),
('Rich Dad Poor Dad', 35),
('The Psychology Of Money', 18),
('The 100$ Startup', 24);

SET SQL_MODE = 'Oracle';

DELIMITER //

CREATE OR REPLACE TRIGGER lib_update_trigger
BEFORE UPDATE 
ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit VALUES (OLD.book_name, OLD.shelf_no, 'UPDATE');
END;

CREATE OR REPLACE TRIGGER lib_delete_trigger
BEFORE DELETE
ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit VALUES (OLD.book_name, OLD.shelf_no, 'DELETE');
END;

//

DELIMITER ;

SELECT *FROM Library_Audit;

UPDATE Library SET shelf_no = 15 WHERE book_name = 'Doglapan';

DELETE FROM Library WHERE book_name = 'The 100$ Startup';

SELECT *FROM Library_Audit;
