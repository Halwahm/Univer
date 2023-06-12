using UnityEngine;

public class Wallscriptt : MonoBehaviour
{
    public float rotationSpeed = 50f;

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            GameObject wall = GameObject.Find("Wall");
            wall.GetComponent<Rigidbody>().constraints = RigidbodyConstraints.FreezePosition;
            wall.GetComponent<Rigidbody>().angularVelocity = Vector3.up * rotationSpeed;
        }
    }
}
