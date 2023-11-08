CREATE TABLE Dept (
    dept_id INT PRIMARY KEY,
    dept_name VARCHAR(50),
    dept_loc VARCHAR(50)
);

CREATE TABLE Project (
    proj_id INT PRIMARY KEY,
    dept_id INT,
    proj_name VARCHAR(50),
    proj_loc VARCHAR(50),
    proj_cost INT,
    proj_year DATE,
    FOREIGN KEY (dept_id) REFERENCES Dept(dept_id)
);

CREATE TABLE Employee(
    emp_id INT PRIMARY KEY,
    dept_id INT,
    emp_name VARCHAR(30),
    emp_position VARCHAR(30),
    emp_salary INT,
    emp_join_date DATE,
    FOREIGN KEY (dept_id) REFERENCES Dept(dept_id)
);


SELECT *FROM Employee NATURAL JOIN Dept;


SELECT *FROM Employee GROUP BY dept_id;


SELECT *FROM Employee INNER JOIN Project ON Employee.Dept_id = Project.Dept_id WHERE NOT Project.Proj_loc = 'Houston';


SELECT *FROM Employee INNER JOIN Dept ON Employee.Dept_id=Dept.Dept_id INNER JOIN Project ON Dept.Dept_id=Project.Dept_id WHERE Project.Proj_year < '2022-01-01'; 


SELECT Dept_id FROM (SELECT Employee.dept_id, COUNT(*) AS cnt FROM EMPLOYEE GROUP BY Dept_id) AS subq WHERE cnt = 2;


SELECT Dept.dept_name FROM Dept WHERE (SELECT COUNT(*) FROM Employee WHERE Employee.dept_id = Dept.dept_id) = 10; 


