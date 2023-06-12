using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RobotController : MonoBehaviour
{
    public float Speed = 5f; 
    
    void Update()
    {
        // движение вперед
        if (Input.GetKey(KeyCode.E))
        {
            transform.Translate(Vector3.forward * Speed * Time.deltaTime);
        }

        // движение назад
        if (Input.GetKey(KeyCode.R))
        {
            transform.Translate(-Vector3.forward * Speed * Time.deltaTime);
        }

        // движение вправо
        if (Input.GetKey(KeyCode.T))
        {
            transform.Translate(Vector3.right * Speed * Time.deltaTime);
        }

        // движение влево
        if (Input.GetKey(KeyCode.Y))
        {
            transform.Translate(-Vector3.right * Speed * Time.deltaTime);
        }
    }
}
