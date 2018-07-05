package com.huekh70.appfinal;

import android.content.Intent;
import android.os.Bundle;

import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;



public class LoginActivity extends BaseActivity {

    private Button mSignin;
    private EditText mUser;
    private EditText mPass;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        mSignin = (Button) findViewById(R.id.btwlogin);
        mUser = (EditText) findViewById(R.id.User);
        mPass = (EditText) findViewById(R.id.Pass);

        mSignin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                SignIn();
            }
        });

    }

    private void SignIn() {
        String UserName = mUser.getText().toString();
        String PassWord = mPass.getText().toString();
        String User1 = "MyGarden";
        String Pass1 = "123456789";

        if ((UserName.equals(User1)) && (PassWord.equals(Pass1))) {
            Toast.makeText(LoginActivity.this, "Login Successfull", Toast.LENGTH_SHORT).show();
            startActivity(new Intent(LoginActivity.this, MainActivity.class));
            finish();
        }
        else {
            Toast.makeText(LoginActivity.this, "Incorrect Username or Password", Toast.LENGTH_SHORT).show();
        }


    }
}
