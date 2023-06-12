﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class TextureChanging : MonoBehaviour
{
    public Texture Texture1;
    public Texture Texture2;
    public Texture Texture3;
    public new GameObject gameObject;
    void Update()
    {
        //Движение
        float x = Input.GetAxis("Horizontal");
        float z = Input.GetAxis("Vertical");
        transform.Translate(x, 0, z);
        float y = Mathf.Clamp(-Input.GetAxis("Mouse X"), -90, 90);
        x = Mathf.Clamp(Input.GetAxis("Mouse Y"), -90, 90);
        transform.Rotate(x, y, 0);

        //Изменение текстуры объекта по нажатию на клавиши
        if (Input.GetKey(KeyCode.Alpha1))
            gameObject.GetComponent<Renderer>().material.mainTexture = Texture1;
        if (Input.GetKey(KeyCode.Alpha2))
            gameObject.GetComponent<Renderer>().material.mainTexture = Texture2;
        if (Input.GetKey(KeyCode.Alpha3))
            gameObject.GetComponent<Renderer>().material.mainTexture = Texture3;
    }

    private void OnCollisionEnter(Collision collision)
    {
        switch (Random.Range(0, 3))
        {
            case 0:
                collision.gameObject.GetComponent<Renderer>().material.mainTexture = Texture1;
                break;
            case 1:
                collision.gameObject.GetComponent<Renderer>().material.mainTexture = Texture2;
                break;
            case 2:
                collision.gameObject.GetComponent<Renderer>().material.mainTexture = Texture3;
                break;
        }

    }
}
