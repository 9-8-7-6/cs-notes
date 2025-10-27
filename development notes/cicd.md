# CI/CD

## Flow
1. Local machine: unit/integration tests + fmt + clippy
2. Push to GIALAB/GitHub or your GitLab
3. CI (dev/staging): detect new commit → build → test → package (Docker) → publish artifact/image
4. Deploy to staging(Kubernetes smoke/E2E)
5. Gate: manual approval and quality check
6. **Deploy** to production
7. Notification
8. Rollback(optional)

## Tools
- Jenkins
- GitHub Actions
- Kubernetes