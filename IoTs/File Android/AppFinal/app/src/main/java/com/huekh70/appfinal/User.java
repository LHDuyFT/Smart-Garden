package com.huekh70.appfinal;

import com.google.firebase.database.IgnoreExtraProperties;

@IgnoreExtraProperties
public class User {

    public int name;

    public User() {
  
    }

    public User(int name) {
        this.name = name;
    }

}
