# https://github.com/sqlalchemy/sqlalchemy/issues/4263


from datetime import datetime
from uuid import uuid4

from sqlalchemy import Column, DateTime, ForeignKey, String, create_engine, event
from sqlalchemy.dialects.postgresql import UUID
from sqlalchemy.event import listens_for
from sqlalchemy.ext.declarative import declarative_base, declared_attr
from sqlalchemy.orm import Session, relationship


def generate_uuid():
    return str(uuid4())


Base = declarative_base()


class User(Base):
    __tablename__ = "users"

    uid = Column(String(36), primary_key=True, unique=True, default=generate_uuid)
    name = Column(String(15), nullable=False)
    description = Column(String(25), nullable=False)
    phone = Column(String(20), nullable=False)
    hash = Column(String(128), nullable=True, unique=True)
    created_on = Column(DateTime(), default=datetime.utcnow)
    updated_on = Column(DateTime(), default=datetime.utcnow, onupdate=datetime.utcnow)


@listens_for(User, "before_insert")
def before_insert_function(mapper, connection, target):
    print("=============")
    print(target.uid)
    print(target.phone)
    print("=============")
    target.hash = "OtherInsert"


@listens_for(User, "before_update")
def before_update_function(mapper, connection, target):
    print("=============")
    print(target.uid)
    print(target.phone)
    print("=============")
    target.hash = "OtherUpdate"


e = create_engine("sqlite://", echo=True)
# engine = create_engine('postgresql://exodus-gw:exodus-gw@localhost:3355/exodus-gw', pool_pre_ping=True)
Base.metadata.create_all(e)
s = Session(e)

import pdb; pdb.set_trace()

u1 = User(phone="asdf", description="asdf", name="asdf")
s.add(u1)
s.commit()

assert u1.hash == "OtherInsert"

u1.description = "some other description"
s.commit()

assert u1.hash == "OtherUpdate"
