package com.huekh70.appfinal;

import android.content.Intent;
import android.os.Bundle;

import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Switch;
import android.view.Menu;
import android.view.MenuItem;

import android.widget.Toast;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.ValueEventListener;


public class MainActivity extends BaseActivity {

    private FirebaseDatabase database = FirebaseDatabase.getInstance();
    private DatabaseReference Temperature = database.getReference("Temperature");
    private DatabaseReference Humidity = database.getReference("Humidity");
    private DatabaseReference Device1 = database.getReference("Device1");
    private DatabaseReference Device2 = database.getReference("Device2");

    private TextView mTemp;
    private TextView mHumi;
    private Switch mSwDv1;
    private Switch mSwDv2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTemp = (TextView) findViewById(R.id.Temp);
        mHumi = (TextView) findViewById(R.id.Humi);
        mSwDv1 = (Switch) findViewById(R.id.SwDv1);
        mSwDv2 = (Switch) findViewById(R.id.SwDv2);

        Temperature.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value = dataSnapshot.getValue(String.class);
                mTemp.setText(value + " ºC");
            }
            @Override
            public void onCancelled(DatabaseError databaseError) {
            }
        });

        Humidity.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value = dataSnapshot.getValue(String.class);
                mHumi.setText(value + " %");
            }
            @Override
            public void onCancelled(DatabaseError databaseError) {
            }
        });

        mSwDv1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (b) {
                    Device1.setValue("true");
                }
                else {
                    Device1.setValue("false");
                }
            }
        });

        mSwDv2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (b) {
                    Device2.setValue("true");
                }
                else {
                    Device2.setValue("false");
                }
            }
        });

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_layout, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id=item.getItemId();
        if (id == R.id.Setting) {
            Toast.makeText(getApplicationContext(), "Not Setting Available", Toast.LENGTH_SHORT).show();
        }
        if (id == R.id.Logout) {
            startActivity(new Intent(MainActivity.this, LoginActivity.class));
            finish();
        }
        if (id == R.id.Exit) {
            finish();
        }
        return super.onOptionsItemSelected(item);
    }
}
