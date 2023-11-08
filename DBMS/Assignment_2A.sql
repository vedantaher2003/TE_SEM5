/*

Assignment No 2A (Employee Schema)
Create following tables in MYSQL
● Employee( Emp_id, Dept_id, Emp_fname, Emp_lname, Emp_Position,
Emp_salary,Emp_JoinDate)
● Dept ( Dept_id, Dept_name,Dept_location ,)
● Project( Proj_id,Dept_id ,Proj_Name,Proj_Location,Proj_cost,Proj_year)

Create view (simple), index, sequence and synonym based on above tables.
Note: Use referential integrity constraints while creating tables with on delete cascade
options.

Use the tables created in assignment no 2 and execute the following queries:

1. Insert at least 10 records in the Employee table and insert other tables accordingly.
2. Display all Employee details with Department ‘Computer’ and ‘IT’ and Employee
first name starting with &#39;p&#39; or &#39;h&#39;.
3. lists the number of different Employee Positions.
4. Give 10% increase in Salary of the Employee whose Birthdate before 1985.
5. Delete Department details which location is ‘Mumbai’.
6. Find the names of Projects with location ‘pune’ .
7. Find the project having cost in between 100000 to 500000.
8. Find the project having maximum price and find average of Project cost
9. Display all employees with Emp _id and Emp name in decreasing order of
Emp_lname
10. Display Proj_name,Proj_location ,Proj_cost of all project started in 2004,2005,2007

*/

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


SELECT *FROM Employee WHERE Employee.dept_id IN 
(SELECT dept_id FROM Dept WHERE dept_name = 'IT' OR dept_name = 'Finance') 
AND Employee.emp_name LIKE 'M%' OR Employee.emp_name LIKE 'R%';


SELECT Employee.emp_position FROM Employee GROUP BY Employee.emp_position;


UPDATE Employee
SET emp_salary = emp_salary + emp_salary * 0.1
WHERE emp_join_date < '2022-01-01';


DELETE FROM Dept
WHERE dept_loc = 'Houston';


SELECT *FROM Project WHERE proj_loc = 'Chicago';


SELECT *FROM Project WHERE proj_cost BETWEEN 30000 AND 50000;


SELECT *FROM Project WHERE proj_cost = (SELECT MAX(proj_cost) FROM Project);


SELECT AVG(proj_cost) FROM Project;


SELECT * FROM Employee ORDER BY emp_name DESC;


CREATE VIEW emp_view AS SELECT *FROM EMPLOYEE;


CREATE INDEX emp_name_indx ON Employee (emp_name); 