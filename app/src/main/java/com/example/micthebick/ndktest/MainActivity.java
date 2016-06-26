package com.example.micthebick.ndktest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {


    private EditText mUIKeyEdit, mUIValueEdit;
    private Spinner mUITypeSpinner;
    private Button mUIGetButton, mUISetButton;
    private Store mStore;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mUIKeyEdit  =   (EditText)findViewById(R.id.key);
        mUIValueEdit    =   (EditText)findViewById(R.id.value);
        mUITypeSpinner  =   (Spinner)findViewById(R.id.type);

        mUIGetButton    =   (Button)findViewById(R.id.GetValue);
        mUISetButton    =   (Button)findViewById(R.id.SetValue);

        mStore  =   new Store();
    }


    private void onGetValue(){

        String  lKey    =   mUIKeyEdit.getText().toString();
        StoreType lType =   (StoreType) mUITypeSpinner.getSelectedItem();

        switch (lType){
            case Integer:
                mUIValueEdit.setText(Integer.toString(mStore.getInteger(lKey)));
                break;
            case String:
                mUIValueEdit.setText(mStore.getString(lKey));
                break;
        }
    }

    private void onSetValue(){

        String lKey =   mUIKeyEdit.getText().toString();
        String lValue   =   mUIValueEdit.getText().toString();
        StoreType lType =   (StoreType)mUITypeSpinner.getSelectedItem();

        try {
            switch (lType){
                case Integer:
                    mStore.setInteger(lKey, Integer.parseInt(lValue));
                    break;
                case String:
                    mStore.setString(lKey, lValue);
                    break;
            }
        }catch (NumberFormatException eNumberFormatException){
            displayError("Incorrect value");
        }
    }

    private void displayError(String pError){
        Toast.makeText(getApplicationContext(), pError, Toast.LENGTH_LONG).show();
    }

    static {
        System.loadLibrary("testNdk");
    }

    public native String testNdk();

}
