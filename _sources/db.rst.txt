Database
========

While I have extensive experience using various databases in team projects, I feel that
my understanding of them lacks a systematic depth. Frequently, I find myself without a
clear resolution for certain database-related challenges.

  - SQL databases: PostgreSQL, SQLite
  - NoSQL databases: DynamoDB, MongoDB, Redis

I intend to conduct a retrospective to consolidate and summarize my experiences with databases.

I believe that databases can be categorized into two major parts: source-related (src-related)
and deployment-related (deploy-related).

  - src-related: how to use databases. 
  - deploy-related: how to configure databases and deploy them.

---

Foreign key violation (src)
~~~~~~~~~~~~~~~~~~~~~~~~~~~

  A primary key generally focuses on the uniqueness of the table.

  A foreign key is generally used to build a relationship between the two tables.

.. code-block:: none

    -- Enable foreign key constraints
    PRAGMA foreign_keys = ON;

    -- Create customers table
    CREATE TABLE customers (
        customer_id INTEGER PRIMARY KEY,
        customer_name TEXT NOT NULL
    );
    
    -- Create orders table with a foreign key reference to customers
    CREATE TABLE orders (
        order_id INTEGER PRIMARY KEY,
        order_number TEXT NOT NULL,
        customer_id INTEGER,
        FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
    );
    
    -- Insert data into customers table
    INSERT INTO customers (customer_id, customer_name) VALUES
        (1, 'Customer A'),
        (2, 'Customer B');
    
    -- Insert data into orders table with a foreign key violation
    INSERT INTO orders (order_id, order_number, customer_id) VALUES
        (101, 'Order 101', 3);  -- This should now cause a foreign key violation


Database migration with Alembic (src)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Key aspects of database migration include:

  1) Schema Changes:

    Database migration involves making changes to the structure of the database,
    such as adding or removing tables, altering columns, or creating indexes.
  
  2) Data Migration:

    Data Transfer: Moving existing data to match the new schema, ensuring that no data is lost during the migration.
    
    Data Transformation: Modifying data as needed to conform to the new schema or data model.
  
  3) Versioning

Thread-safety issues (src)
~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Debug a multi-thread issue with `threading.Lock`

.. code-block:: python

     import logging
     import os
     from urllib.parse import urljoin
    +from threading import Lock
    +
    +LOCK = Lock()

     import requests
     from requests.packages.urllib3.util.retry import Retry  # pylint: disable=import-error
    @@ -68,9 +71,11 @@ class HTTPFetcher(Fetcher):
                 remote_path, stream=True, allow_redirects=True, timeout=self.timeout
             )
             response.raise_for_status()
    -        with open(local_path, "wb") as local_file:
    -            for chunk in response.iter_content(chunk_size=1024):
    -                local_file.write(chunk)
    +        with LOCK:
    +            import pdb; pdb.set_trace()
    +            with open(local_path, "wb") as local_file:
    +                for chunk in response.iter_content(chunk_size=1024):
    +                    local_file.write(chunk)
             return local_path

         def fetch(self, path, download_root):


2) Lazy initialization and thread-safety

What's lazy initialization?

Lazy initialization is a design pattern where an object or resource 
is not created until it is actually needed.

When lazy initialization is used in a multithreaded environment, potential issues 
can arise if multiple threads attempt to access the uninitialized resource 
simultaneously, zum beispiel "race conditions".


Use the lightweight sqlite for unit test (src)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Using SQLite for unit testing is a common and effective approach.
Set up and tear down the necessary database fixtures for each test. This ensures 
a consistent starting point for your tests and prevents interference between different 
test cases.

.. code-block:: python

    @pytest.fixture(autouse=True)
    def sqlite_in_tests():
        """Any 'real' usage of sqlalchemy during this test suite makes use of
        a fresh sqlite DB for each test run.
        """

        remove_old_db_files()
        set_env_vars()
        ...

    @pytest.fixture(autouse=True)
    def sqlite_broker_in_tests(sqlite_in_tests):
        """Decouple the sqlite initialization and usage by broker.
        """
        set_broker()
        ...

